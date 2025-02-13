#include "CServer.h"
#include "ConfigMgr.h"
#include "const.h"

int main() {
    try {
        ConfigMgr gCfgMgr;
        std::string gate_port_str = gCfgMgr["GateServer"]["Port"];
        unsigned short gate_port = atoi(gate_port_str.c_str());

        net::io_context ioc{ 1 };
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {
            if (error) {
                return;
            }

            ioc.stop();
        });

        std::make_shared<CServer>(ioc, gate_port)->Start();
        std::cout << "Gate Server listen to Port " << gate_port << std::endl;
        ioc.run();
    } catch (std::exception& exp) {
        std::cerr << "Error: " << exp.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
