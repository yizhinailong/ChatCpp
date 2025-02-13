#pragma once
#include <grpcpp/grpcpp.h>

#include "Singleton.h"
#include "const.h"
#include "message.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;

class VarifyGrpcClient : public Singleton<VarifyGrpcClient> {
    friend class Singleton<VarifyGrpcClient>;

public:
    GetVarifyRsp GetVarifyCode(std::string email);

private:
    VarifyGrpcClient();

    std::unique_ptr<VarifyService::Stub> stub_;
};
