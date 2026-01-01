#include "LoginSystem.hpp"

#include "HttpConnection.hpp"

LoginSystem::~LoginSystem() {
}

void LoginSystem::RegisterGetHandler(std::string url, HttpHandler handler) {
    m_get_handlers.insert(make_pair(url, handler));
}

LoginSystem::LoginSystem() {
    RegisterGetHandler(
        "/get_test",
        [](std::shared_ptr<HttpConnection> connection) {
            beast::ostream(connection->m_response.body()) << "This is get test response.\r\n";
        });
}

bool LoginSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> connection) {
    if (m_get_handlers.find(path) == m_get_handlers.end()) {
        return false;
    }

    m_get_handlers[path](connection);
    return true;
}
