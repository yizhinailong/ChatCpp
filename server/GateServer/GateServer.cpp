#include "CServer.hpp"

int main() {
    try {
        auto port = static_cast<unsigned short>(8080);
        net::io_context ioc{ 1 };
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait(
            [&ioc](const boost::system::error_code& ec, int signal_number) {
                if (ec) {
                    return;
                }

                ioc.stop();
            });

        std::make_shared<CServer>(ioc, port)->Start();
        ioc.run();
    } catch (const std::exception& exp) {
        std::cerr << "GateServer exception is " << exp.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
