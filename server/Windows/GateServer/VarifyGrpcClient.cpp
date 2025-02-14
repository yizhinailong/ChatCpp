#include "VarifyGrpcClient.h"

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/impl/status.h>
#include <grpcpp/security/credentials.h>
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>

#include "ConfigMgr.h"
#include "const.h"
#include "message.grpc.pb.h"
#include "message.pb.h"

RPConPool::RPConPool(size_t poolsize, std::string host, std::string port)
    : poolSize_(poolsize), host_(host), port_(port), b_stop_(false) {
    for (int i = 0; i < poolSize_; i++) {
        std::shared_ptr<Channel> channel = grpc::CreateChannel(
            host + ":" + port, grpc::InsecureChannelCredentials());
        connections_.push(VarifyService::NewStub(channel));
    }
}

RPConPool::~RPConPool() {
    std::lock_guard<std::mutex> lock(mutex_);
    Close();
    while (!connections_.empty()) {
        connections_.pop();
    }
}

void RPConPool::Close() {
    b_stop_ = true;
    cond_.notify_all();
}

std::unique_ptr<VarifyService::Stub> RPConPool::getConnection() {
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this]() {
        if (b_stop_) {
            return true;
        }
        return !connections_.empty();
    });

    if (b_stop_) {
        return nullptr;
    }

    auto context = std::move(connections_.front());
    connections_.pop();
    return context;
}

void RPConPool::returnConnection(std::unique_ptr<VarifyService::Stub> context) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (b_stop_) {
        return;
    }

    connections_.push(std::move(context));
    cond_.notify_one();
}

VarifyGrpcClient::VarifyGrpcClient() {
    auto& gCfgMgr = ConfigMgr::Inst();
    std::string host = gCfgMgr["VarifyServer"]["Host"];
    std::string port = gCfgMgr["VarifyServer"]["Port"];
    pool_.reset(new RPConPool(10, host, port));
}

GetVarifyRsp VarifyGrpcClient::GetVarifyCode(std::string email) {
    ClientContext context;
    GetVarifyReq request;
    GetVarifyRsp reply;

    request.set_email(email);

    auto stub = pool_->getConnection();
    Status status = stub->GetVarifyCode(&context, request, &reply);
    if (!status.ok()) {
        reply.set_error(ErrorCodes::RPCFailed);
    }

    pool_->returnConnection(std::move(stub));
    return reply;
}
