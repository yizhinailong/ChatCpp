#pragma once

#include "Const.hpp"

class CServer : public std::enable_shared_from_this<CServer> {
public:
    CServer(boost::asio::io_context& ioc, unsigned short& port);

    void Start();

private:
    net::io_context& m_ioc;
    tcp::acceptor m_accpetor;
};
