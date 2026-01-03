#include "AsioIOServeicePool.hpp"

#include <iostream>
#include <memory>

AsioIOServicePool::AsioIOServicePool(std::size_t size)
    : m_io_services(size),
      m_works(size),
      m_next_io_service(0) {
    for (std::size_t i = 0; i < size; ++i) {
        m_works[i] = std::make_unique<Work>(boost::asio::make_work_guard(m_io_services[i]));
    }

    // 遍历多个ioservice，创建多个线程，每个线程内部启动ioservice
    for (std::size_t i = 0; i < m_io_services.size(); ++i) {
        m_threads.emplace_back([this, i]() {
            m_io_services[i].run();
        });
    }
}

AsioIOServicePool::~AsioIOServicePool() {
    Stop();
    std::cout << "AsioIOServicePool destruct" << std::endl;
}

boost::asio::io_context& AsioIOServicePool::GetIOService() {
    auto& service = m_io_services[m_next_io_service++];
    if (m_next_io_service == m_io_services.size()) {
        m_next_io_service = 0;
    }
    return service;
}

void AsioIOServicePool::Stop() {
    // 因为仅仅执行work.reset并不能让iocontext从run的状态中退出
    // 当io_context已经绑定了读或写的监听事件后，还需要手动stop该服务。
    for (std::size_t i = 0; i < m_works.size(); ++i) {
        // 把服务先停止
        m_io_services[i].stop();
        m_works[i].reset();
    }

    for (auto& t : m_threads) {
        t.join();
    }
}
