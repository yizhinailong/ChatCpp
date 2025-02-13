#include "VarifyGrpcClient.h"

VarifyGrpcClient::VarifyGrpcClient() {
    std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials());
    stub_ = VarifyService::NewStub(channel);
}

GetVarifyRsp VarifyGrpcClient::GetVarifyCode(std::string email) {
    ClientContext context;
    GetVarifyReq request;
    GetVarifyRsp reply;

    request.set_email(email);

    Status status = stub_->GetVarifyCode(&context, request, &reply);
    if (!status.ok()) {
        reply.set_error(ErrorCodes::RPCFailed);
    }

    return reply;
}
