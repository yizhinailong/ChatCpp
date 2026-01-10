#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <memory>

#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

#include "Singleton.hpp"

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>

using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

const std::string CODEPREFIX = "code_";

enum class ErrorCode : std::uint16_t {
    SUCCESS,
    ERROR_JSON,
    RPCFAILED,
    VERIFY_EXPIRED,
    USER_EXIST,
    VERIFY_CODE_ERROR,
};
