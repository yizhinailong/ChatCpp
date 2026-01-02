#include "HttpConnection.hpp"

#include "LoginSystem.hpp"

HttpConnection::HttpConnection(tcp::socket socket)
    : m_socket(std::move(socket)) {}

void HttpConnection::Start() {
    auto self = shared_from_this();
    http::async_read(
        m_socket,
        m_buffer,
        m_request,
        [self](beast::error_code ec, std::size_t bytes_transgerred) {
            try {
                if (ec) {
                    std::cout << "Http read error is " << ec.what() << std::endl;
                    return;
                }

                boost::ignore_unused(bytes_transgerred);
                self->HandleRequest();
                self->CheckDeadline();
            } catch (const std::exception& exp) {
                std::cout << "Http exception is " << exp.what() << std::endl;
            }
        });
}

void HttpConnection::CheckDeadline() {
    auto self = shared_from_this();
    m_deadline.async_wait([self](beast::error_code ec) {
        if (!ec) {
            self->m_socket.close(ec);
        }
    });
}

void HttpConnection::WriteResponse() {
    auto self = shared_from_this();
    m_response.content_length(m_response.body().size());
    http::async_write(
        m_socket,
        m_response,
        [self](beast::error_code ec, std::size_t bytes_transferred) {
            self->m_socket.shutdown(tcp::socket::shutdown_send, ec);
            self->m_deadline.cancel();
        });
}

static unsigned char ToHex(unsigned char x) {
    return x > 9 ? x + 55 : x + 48;
}

static unsigned char FromHex(unsigned char x) {
    unsigned char y = 0;
    if (x >= 'A' && x <= 'Z') {
        y = x - 'A' + 10;
    } else if (x >= 'a' && x <= 'z') {
        y = x - 'a' + 10;
    } else if (x >= '0' && x <= '9') {
        y = x - '0';
    }
    return y;
}

static std::string UrlEncode(const std::string& str) {
    std::string str_temp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++) {
        // 判断是否仅有数字和字母构成
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~')) {
            str_temp += str[i];
        } else if (str[i] == ' ') { // 为空字符
            str_temp += "+";
        } else {
            // 其他字符需要提前加%并且高四位和低四位分别转为16进制
            str_temp += '%';
            str_temp += ToHex((unsigned char)str[i] >> 4);
            str_temp += ToHex((unsigned char)str[i] & 0x0F);
        }
    }
    return str_temp;
}

static std::string UrlDecode(const std::string& str) {
    std::string str_temp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++) {
        // 还原+为空
        if (str[i] == '+') {
            str_temp += ' ';
        }
        // 遇到%将后面的两个字符从16进制转为char再拼接
        else if (str[i] == '%') {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low = FromHex((unsigned char)str[++i]);
            str_temp += high * 16 + low;
        } else {
            str_temp += str[i];
        }
    }
    return str_temp;
}

void HttpConnection::PreParseGetParam() {
    // 提取 URL
    auto url = m_request.target();
    // 查找查询字符串的开始位置（即 '?' 的位置）
    auto query_pos = url.find('?');
    if (query_pos == std::string::npos) {
        m_get_url = url;
        return;
    }

    m_get_url = url.substr(0, query_pos);
    std::string query_string = url.substr(query_pos + 1);
    std::string key;
    std::string value;
    std::size_t pos = 0;
    while ((pos = query_string.find('&')) != std::string::npos) {
        auto pair = query_string.substr(0, pos);
        std::size_t eq_pos = pair.find('=');
        if (eq_pos != std::string::npos) {
            key = UrlDecode(pair.substr(0, eq_pos)); // 假设有 url_decode 函数来处理URL解码
            value = UrlDecode(pair.substr(eq_pos + 1));
            m_get_params[key] = value;
        }
        query_string.erase(0, pos + 1);
    }
    // 处理最后一个参数对（如果没有 & 分隔符）
    if (!query_string.empty()) {
        std::size_t eq_pos = query_string.find('=');
        if (eq_pos != std::string::npos) {
            key = UrlDecode(query_string.substr(0, eq_pos));
            value = UrlDecode(query_string.substr(eq_pos + 1));
            m_get_params[key] = value;
        }
    }
}

void HttpConnection::HandleRequest() {
    // 设置版本
    m_response.version(m_request.version());
    m_response.keep_alive(false);
    if (m_request.method() == http::verb::get) {
        PreParseGetParam();
        bool success = LoginSystem::GetInstance()->HandleGet(m_get_url, shared_from_this());
        if (!success) {
            m_response.result(http::status::not_found);
            m_response.set(http::field::content_type, "text/plain");
            beast::ostream(m_response.body()) << "Url not found\r\n";
            WriteResponse();
            return;
        }

        m_response.result(http::status::ok);
        m_response.set(http::field::server, "GateServer");
        WriteResponse();
        return;
    } else if (m_request.method() == http::verb::post) {
        bool success = LoginSystem::GetInstance()->HandlePost(m_request.target(), shared_from_this());
        if (!success) {
            m_response.result(http::status::not_found);
            m_response.set(http::field::content_type, "text/plain");
            beast::ostream(m_response.body()) << "Url not found\r\n";
            WriteResponse();
            return;
        }

        m_response.result(http::status::ok);
        m_response.set(http::field::server, "GateServer");
        WriteResponse();
        return;
    }
}
