#include "CServer.hpp"

#include "HttpConnection.hpp"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port)
    : m_ioc(ioc),
      m_accpetor(ioc, tcp::endpoint(tcp::v4(), port)),
      m_socket(ioc) {}

void CServer::Start() {
    auto self = shared_from_this();
    m_accpetor.async_accept(
        m_socket,
        [self](beast::error_code ec) {
            try {
                // 出错放弃这个连接，继续接受下一个连接
                if (ec) {
                    self->Start();
                    return;
                }

                // 创建新的连接，并且创建 HttpConnection 对象来处理这个连接
                std::make_shared<HttpConnection>(std::move(self->m_socket))->Start();

                // 继续监听
                self->Start();
            } catch (const std::exception& exp) {
                std::cerr << "CServer accept exception is " << exp.what() << std::endl;
                return;
            }
        });
}
