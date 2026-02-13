# ChatCpp PROJECT KNOWLEDGE BASE

**Generated:** 2026-02-13
**Commit:** ece7f45
**Branch:** main

## OVERVIEW
C++ full-stack chat application: Qt6 client + Boost.Beast HTTP gateway + Node.js gRPC verification service. Multi-language microservices architecture with MySQL/Redis backends.

## STRUCTURE
```
ChatCpp/
├── client/chat-widget/           # Qt6 desktop GUI (QMake build)
│   ├── main.cpp                  # QApplication entry
│   ├── httpmgr.cpp/hpp           # QNetworkAccessManager wrapper
│   ├── logindialog.cpp/hpp       # Login UI
│   ├── registerdialog.cpp/hpp    # Registration UI
│   ├── global.cpp/hpp            # RequestId/Modules/ErrorCodes enums
│   ├── res/                      # PNG icons
│   └── style/stylesheet.qss      # Qt stylesheets
├── server/GateServer/            # C++20 HTTP gateway (Visual Studio)
│   ├── GateServer.cpp/hpp        # HTTP server entry with Asio
│   ├── CServer.cpp/hpp           # Async acceptor
│   ├── HttpConnection.cpp/hpp    # Beast request/response handler
│   ├── LoginSystem.cpp/hpp       # URL router
│   ├── MySQLDao.cpp/hpp          # Connection pool, CRUD
│   ├── RedisMgr.cpp/hpp          # Redis client wrapper
│   ├── VerifyGrpcClient.cpp/hpp  # gRPC client for VerifyServer
│   ├── AsioIOServicePool.cpp/hpp # Thread pool for io_context
│   ├── ConfigMgr.cpp/hpp         # INI config parser
│   ├── Singleton.hpp             # std::call_once singleton template
│   └── message.proto             # Protobuf for VerifyService
├── server/VerifyServer/          # Node.js/Bun gRPC service
│   ├── server.js                 # gRPC server entry (port 50051)
│   ├── proto.js                  # Protobuf loader
│   ├── email.js                  # nodemailer SMTP
│   ├── redis.js                  # ioredis client
│   ├── const.js                  # Error codes
│   ├── config.js                 # JSON config loader
│   └── message.proto             # Protobuf (duplicate)
└── docs/                         # 36 daily tutorials (Chinese)
```

## WHERE TO LOOK
| Task | Location | Notes |
|------|----------|-------|
| **CLIENT** |||
| Client entry | `client/chat-widget/main.cpp` | QApplication init, stylesheet load |
| HTTP client | `client/chat-widget/httpmgr.cpp` | QNetworkAccessManager wrapper, singleton |
| Login UI | `client/chat-widget/logindialog.cpp` | Qt form with HTTP integration |
| Register UI | `client/chat-widget/registerdialog.cpp` | Qt form with HTTP integration |
| Constants | `client/chat-widget/global.cpp/hpp` | RequestId, Modules, ErrorCodes enums |
| **GATESERVER** |||
| Gateway entry | `server/GateServer/GateServer.cpp` | HTTP server + Asio |
| HTTP routing | `server/GateServer/LoginSystem.cpp` | Maps URLs to std::function handlers |
| Request handling | `server/GateServer/HttpConnection.cpp` | Beast async_read/write, JSON parsing |
| Database | `server/GateServer/MySQLDao.cpp` | MySqlPool with mutex+condition_variable |
| gRPC calls | `server/GateServer/VerifyGrpcClient.cpp` | Calls VerifyServer.GetVerifyCode() |
| Thread pool | `server/GateServer/AsioIOServicePool.cpp` | Distributes io_context round-robin |
| **VERIFYSERVER** |||
| gRPC entry | `server/VerifyServer/server.js` | Loads config.json, starts gRPC |
| Email sending | `server/VerifyServer/email.js` | nodemailer SMTP transport |
| Redis caching | `server/VerifyServer/redis.js` | ioredis client for code storage |
| **CONFIG** |||
| GateServer config | `server/GateServer/config.ini` | Ports, hosts, MySQL/Redis/gRPC |
| Client config | `client/chat-widget/config.ini` | GateServer connection settings |
| VerifyServer config | `server/VerifyServer/config.json` | Email, MySQL, Redis sections |

## CODE MAP

**Key Patterns:**
- **Singleton**: `Singleton<T>` template with `std::call_once`
- **CRTP**: `HttpMgr<HttpMgr>` inherits `Singleton<HttpMgr>`
- **Async IO**: `AsioIOServicePool` thread pool, `enable_shared_from_this` pattern
- **Connection Pooling**: `MySqlPool` with mutex + condition_variable
- **Handler Map**: `LoginSystem` registers URL → `std::function` handlers

**Communication Flow:**
```
Client (Qt) → HTTP POST (JSON) → GateServer (Boost.Beast)
GateServer → gRPC (protobuf) → VerifyServer (Node.js)
VerifyServer → Email (SMTP) → User Email
```

## CONVENTIONS

### Client (Qt)
- **HTTP requests**: `HttpMgr::GetInstance().Post(url, json, callback)`
- **UI refresh**: Call `repolish(widget)` after stylesheet changes (defined in global.hpp)
- **Config**: Read `config.ini` with QSettings for GateServer port
- **Enums**: `RequestId::ID_GET_VERIFY_CODE`, `RequestId::ID_REGISTER_USER` for request tracking

### GateServer (C++)
- **Handler registration**: `LoginSystem::RegisterGetHandler("/path", handler)` or `RegisterPostHandler()`
- **Config access**: `ConfigMgr::GetInstance()["Section"]["Key"]`
- **gRPC calls**: `VerifyGrpcClient::GetInstance().GetVerifyCode(email)`
- **Async patterns**: `enable_shared_from_this` for async handlers

### VerifyServer (Node.js)
- **gRPC service**: `VerifyService.GetVerifyCode(email)` returns error, email, code
- **Runtime**: Uses Bun (`bun server.js`) not Node.js
- **Redis**: Stores email→code mapping with TTL

## ANTI-PATTERNS (THIS PROJECT)

### All Components
- **Never commit build artifacts**: `build/`, `x64/`, `*.obj`, `*.pdb`, `*.dll`
- **Never hardcode credentials**: Move to .env files (currently in config.ini/config.json)
- **No proper logging**: std::cout (C++), qDebug (Qt), console.log (JS) - use spdlog/winston

### GateServer
- **No database user check**: TODO at LoginSystem.cpp:102 for registration

### VerifyServer
- **Duplicate message.proto**: Same file exists in GateServer/ (DRY violation)
- **No test suite**: No tests despite being microservice

### Client
- **Tight UI-logic coupling**: HTTP calls embedded directly in dialog widgets

## UNIQUE STYLES
- **Multi-language build systems**: QMake (Qt), Visual Studio (C++), Bun (Node.js) - no unification
- **Hybrid communication**: HTTP for client, gRPC for server-to-server, planned TCP for chat
- **Shared Redis**: Both C++ GateServer and Node.js VerifyServer connect to same Redis instance
- **Chinese documentation**: All docs/ files are Chinese (day01-day36 tutorials)
- **sccache integration**: Qt client uses `QMAKE_CXX = sccache` for compilation caching

## COMMANDS
```bash
# Build Qt client (Windows)
cd client/chat-widget
qmake chat-widget.pro
nmake

# Build GateServer (Windows)
open server/GateServer/GateServer.sln

# Run VerifyServer (Bun runtime)
cd server/VerifyServer
bun server.js

# Format code (Google style)
clang-format -i --style=file *.cpp *.hpp
```

## NOTES
- **TODO**: `LoginSystem.cpp:102` - missing database user existence check in registration
- **Security**: Credentials exposed in config files (mysql, redis, email passwords)
- **Repository size**: 4.3GB due to committed build artifacts (x64/, build/, node_modules/)
- **Platform**: Windows-focused (Visual Studio projects), Linux mentioned in docs
- **gRPC**: Protobuf definitions duplicated in GateServer/ and VerifyServer/ (message.proto)
- **No testing**: No unit tests, test frameworks, or CI/CD pipelines
- **Day-by-day docs**: 36-day development log in docs/ - read for implementation details
