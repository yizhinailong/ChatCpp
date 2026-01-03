#pragma once

#include <vector>

#include <boost/asio.hpp>

#include "Singleton.hpp"

class AsioIOServicePool : public Singleton<AsioIOServicePool> {
    friend Singleton<AsioIOServicePool>;

public:
    using IOService = boost::asio::io_context;
    using Work = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;
    using WorkPtr = std::unique_ptr<Work>;

    ~AsioIOServicePool();
    AsioIOServicePool(const AsioIOServicePool&) = delete;
    AsioIOServicePool& operator=(const AsioIOServicePool&) = delete;
    // 使用 round-robin 的方式返回一个 io_service
    void Stop();

    boost::asio::io_context& GetIOService();

private:
    AsioIOServicePool(std::size_t size = std::thread::hardware_concurrency());

    std::vector<IOService> m_io_services;
    std::vector<WorkPtr> m_works;
    std::vector<std::thread> m_threads;
    std::size_t m_next_io_service;
};
