#include "VerifyGrpcClient.hpp"

VerifyGrpcClient::VerifyGrpcClient() {
    std::shared_ptr<Channel> channel = grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials());
    m_stub = VerifyService::NewStub(channel);
}

GetVerifyResponse VerifyGrpcClient::GetVerifyCode(std::string email) {
    ClientContext context;
    GetVerifyResponse reply;
    GetVerifyRequest request;

    request.set_email(email);
    Status status = m_stub->GetVerifyCode(&context, request, &reply);
    if (!status.ok()) {
        reply.set_error(static_cast<std::uint16_t>(ErrorCode::RPCFAILED));
    }

    return reply;
}
