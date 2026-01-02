#include "LoginSystem.hpp"

#include "HttpConnection.hpp"

LoginSystem::~LoginSystem() {
}

void LoginSystem::RegisterGetHandler(std::string url, HttpHandler handler) {
    m_get_handlers.insert(make_pair(url, handler));
}

void LoginSystem::RegisterPostHandler(std::string url, HttpHandler handler) {
    m_post_handlers.insert(make_pair(url, handler));
}

LoginSystem::LoginSystem() {
    RegisterGetHandler(
        "/get_test",
        [](std::shared_ptr<HttpConnection> connection) {
            beast::ostream(connection->m_response.body()) << "This is get test response.\r\n";
            int i = 0;
            for (auto& elem : connection->m_get_params) {
                i++;
                beast::ostream(connection->m_response.body())
                    << "Get param " << i << " : key = " << elem.first
                    << ", value = " << elem.second << "\r\n";
            }
        });

    RegisterPostHandler(
        "/get_verify_code",
        [](std::shared_ptr<HttpConnection> connection) {
            auto body_str = boost::beast::buffers_to_string(connection->m_request.body().data());
            std::cout << "Post body is\n"
                      << body_str << std::endl;
            connection->m_response.set(http::field::content_type, "text/json");
            Json::Value root;
            Json::Reader reader;
            Json::Value src_root;

            bool parse_success = reader.parse(body_str, src_root);
            if (!parse_success || !src_root.isMember("email")) {
                std::cout << "Failed to parse JSON data." << std::endl;
                root["error"] = static_cast<std::uint16_t>(ErrorCode::ERROR_JSON);
                std::string json_str = root.toStyledString();
                beast::ostream(connection->m_response.body()) << json_str;
                return;
            }

            auto email = src_root["email"].asString();
            std::cout << "Email is " << email << std::endl;
            root["error"] = static_cast<std::uint16_t>(ErrorCode::SUCCESS);
            root["email"] = src_root["email"];
            std::string json_str = root.toStyledString();
            beast::ostream(connection->m_response.body()) << json_str;
            return;
        });
}

bool LoginSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> connection) {
    if (m_get_handlers.find(path) == m_get_handlers.end()) {
        return false;
    }

    m_get_handlers[path](connection);
    return true;
}

bool LoginSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> connection) {
    if (m_post_handlers.find(path) == m_post_handlers.end()) {
        return false;
    }

    m_post_handlers[path](connection);
    return true;
}
