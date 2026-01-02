#pragma once

#include <grpcpp/grpcpp.h>

#include "message.grpc.pb.h"

#include "Const.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using message::GetVerifyRequest;
using message::GetVerifyResponse;
using message::VerifyService;

class VerifyGrpcClient : public Singleton<VerifyGrpcClient> {
    friend class Singleton<VerifyGrpcClient>;

public:
    GetVerifyResponse GetVerifyCode(std::string email);

private:
    VerifyGrpcClient();

    std::unique_ptr<VerifyService::Stub> m_stub;
};
