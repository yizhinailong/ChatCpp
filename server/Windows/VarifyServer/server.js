const grpc = require("@grpc/grpc-js");
const message_proto = require("./proto");
const const_module = require("./const");
const { v4: uuidv4 } = require("uuid");
const emailModule = require("./email");
// const redis_module = require("./redis");

async function GetVarifyCode(call, callback) {
  console.log("email is ", call.request.email);
  try {
    uniqueId = uuidv4();
    console.log("uniqueId is ", uniqueId);
    let text_str = "您的验证码为\n" + uniqueId + "\n请三分钟内完成注册";
    //发送邮件
    let mailOptions = {
      from: "liufeng3286773258@163.com",
      to: call.request.email,
      subject: "验证码",
      text: text_str,
    };
    let send_res = await emailModule.SendMail(mailOptions);
    console.log("send res is ", send_res);
    callback(null, { email: call.request.email, error: const_module.Errors.Success });
  } catch (error) {
    console.log("catch error is ", error);
    callback(null, { email: call.request.email, error: const_module.Errors.Exception });
  }
}

function main() {
  var server = new grpc.Server();
  server.addService(message_proto.VarifyService.service, { GetVarifyCode: GetVarifyCode });
  server.bindAsync("127.0.0.1:50051", grpc.ServerCredentials.createInsecure(), () => {
    console.log("grpc server started");
  });
}

main();
