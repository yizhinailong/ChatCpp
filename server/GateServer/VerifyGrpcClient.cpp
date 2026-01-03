#include "VerifyGrpcClient.hpp"

#include "ConfigMgr.hpp"

RPConnectionPool::RPConnectionPool(std::size_t pool_size, std::string host, std::string port)
    : m_pool_size(pool_size),
      m_host(host),
      m_port(port),
      m_b_stoop(false) {
    for (int i = 0; i < m_pool_size; i++) {
        std::shared_ptr<Channel> channel = grpc::CreateChannel(
            m_host + ":" + m_port,
            grpc::InsecureChannelCredentials());
        m_connections.push(VerifyService::NewStub(channel));
    }
}

RPConnectionPool::~RPConnectionPool() {
    std::lock_guard<std::mutex> lock(m_mutex);
    Close();
    while (!m_connections.empty()) {
        m_connections.pop();
    }
}

void RPConnectionPool::Close() {
    m_b_stoop = true;
    m_condition.notify_all();
}

void RPConnectionPool::ReturnConnection(std::unique_ptr<VerifyService::Stub> context) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_b_stoop) {
        return;
    }

    m_connections.push(std::move(context));
    m_condition.notify_one();
}

auto RPConnectionPool::GetConnection() -> std::unique_ptr<VerifyService::Stub> {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition.wait(lock, [this]() {
        if (m_b_stoop) {
            return true;
        }
        return !m_connections.empty();
    });

    if (m_b_stoop) {
        return nullptr;
    }

    auto context = std::move(m_connections.front());
    m_connections.pop();
    return context;
}

VerifyGrpcClient::VerifyGrpcClient() {
    auto& g_cfg = ConfigMgr::GetInstance();
    std::string host = g_cfg["VerifyServer"]["Host"];
    std::string port = g_cfg["VerifyServer"]["Port"];
    m_connection_pool.reset(new RPConnectionPool(5, host, port));
}

GetVerifyResponse VerifyGrpcClient::GetVerifyCode(std::string email) {
    ClientContext context;
    GetVerifyResponse reply;
    GetVerifyRequest request;

    request.set_email(email);
    auto stub = m_connection_pool->GetConnection();
    Status status = stub->GetVerifyCode(&context, request, &reply);
    if (!status.ok()) {
        reply.set_error(static_cast<std::uint16_t>(ErrorCode::RPCFAILED));
    }
    m_connection_pool->ReturnConnection(std::move(stub));

    return reply;
}
