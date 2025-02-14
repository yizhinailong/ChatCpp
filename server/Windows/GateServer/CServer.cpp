#include "CServer.h"

#include "AsioIOServicePool.h"
#include "HttpConnection.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port)
    : _ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {
}

void CServer::Start() {
    auto self = shared_from_this();
    auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
    std::shared_ptr<HttpConnection> new_connection = std::make_shared<HttpConnection>(io_context);
    _acceptor.async_accept(new_connection->GetSocket(), [self, new_connection](beast::error_code ec) {
        try {
            if (ec) {
                self->Start();
                return;
            }

            new_connection->Start();

            self->Start();
        } catch (std::exception& exp) {
            std::cout << "Exception is " << exp.what() << std::endl;
        }
    });
}
