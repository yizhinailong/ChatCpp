#pragma once

#include "Const.hpp"

class HttpConnection : public std::enable_shared_from_this<HttpConnection> {
public:
    friend class LoginSystem;
    HttpConnection(tcp::socket socket);

    void Start();

private:
    void CheckDeadline();
    void WriteResponse();
    void HandleRequest();

    tcp::socket m_socket;                                                              // 连接状态
    beast::flat_buffer m_buffer{ 8192 };                                               // 连接缓冲区
    http::request<http::dynamic_body> m_request;                                       // 处理的请求
    http::response<http::dynamic_body> m_response;                                     // 响应对象
    net::steady_timer m_deadline{ m_socket.get_executor(), std::chrono::seconds(60) }; // 连接超时定时器
};
