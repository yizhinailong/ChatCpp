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

void HttpConnection::HandleRequest() {
    // 设置版本
    m_response.version(m_request.version());
    m_response.keep_alive(false);
    if (m_request.method() == http::verb::get) {
        bool success = LoginSystem::GetInstance()->HandleGet(m_request.target(), shared_from_this());
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
