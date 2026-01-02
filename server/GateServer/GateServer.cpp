#include "CServer.hpp"
#include "ConfigMgr.hpp"

int main() {
    try {
        ConfigMgr g_cfg;
        std::string gate_port_str = g_cfg["GateServer"]["Port"];
        unsigned short gate_port = atoi(gate_port_str.c_str());

        net::io_context ioc{ 1 };
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait(
            [&ioc](const boost::system::error_code& ec, int signal_number) {
                if (ec) {
                    return;
                }

                ioc.stop();
            });
        std::make_shared<CServer>(ioc, gate_port)->Start();
        std::cout << "GateServer started at http://127.0.0.1:" << gate_port << std::endl;
        std::cout << "GateServer is running..." << std::endl;
        ioc.run();
    } catch (const std::exception& exp) {
        std::cerr << "GateServer exception is " << exp.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
