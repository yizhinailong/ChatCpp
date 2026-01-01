#pragma once

#include "Const.hpp"

class HttpConnection;
using HttpHandler = std::function<void(std::shared_ptr<HttpConnection>)>;

class LoginSystem : public Singleton<LoginSystem> {
    friend class Singleton<LoginSystem>;

public:
    ~LoginSystem();

    bool HandleGet(std::string path, std::shared_ptr<HttpConnection> conneciton);
    void RegisterGetHandler(std::string url, HttpHandler handler);

private:
    LoginSystem();

    std::map<std::string, HttpHandler> m_get_handlers;
    std::map<std::string, HttpHandler> m_post_handlers;
};
