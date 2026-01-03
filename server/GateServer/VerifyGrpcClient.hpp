#pragma once

#include <queue>

#include <grpcpp/grpcpp.h>

#include "message.grpc.pb.h"

#include "Const.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using message::GetVerifyRequest;
using message::GetVerifyResponse;
using message::VerifyService;

class RPConnectionPool {
public:
    RPConnectionPool(std::size_t pool_size, std::string host, std::string port);
    ~RPConnectionPool();

    void Close();
    void ReturnConnection(std::unique_ptr<VerifyService::Stub> context);
    auto GetConnection() -> std::unique_ptr<VerifyService::Stub>;

private:
    std::atomic<bool> m_b_stoop;
    std::size_t m_pool_size;
    std::string m_host;
    std::string m_port;
    std::queue<std::unique_ptr<VerifyService::Stub>> m_connections;
    std::condition_variable m_condition;
    std::mutex m_mutex;
};

class VerifyGrpcClient : public Singleton<VerifyGrpcClient> {
    friend class Singleton<VerifyGrpcClient>;

public:
    GetVerifyResponse GetVerifyCode(std::string email);

private:
    VerifyGrpcClient();

    std::unique_ptr<RPConnectionPool> m_connection_pool;
};
