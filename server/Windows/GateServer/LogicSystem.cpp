#include "LogicSystem.h"

#include "HttpConnection.h"

LogicSystem::LogicSystem() {
    RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {
        beast::ostream(connection->_response.body()) << "receive get_test request";
    });
}

LogicSystem::~LogicSystem() {
}

bool LogicSystem::HandleGet(std::string patch, std::shared_ptr<HttpConnection> connection) {
    if (_get_handlers.find(patch) == _get_handlers.end()) {
        return false;
    }

    _get_handlers[patch](connection);
    return true;
}

void LogicSystem::RegGet(std::string url, HttpHandler handler) {
    _get_handlers.insert(std::make_pair(url, handler));
}
