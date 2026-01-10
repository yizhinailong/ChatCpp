#include "RedisMgr.hpp"

#include <chrono>

#include "ConfigMgr.hpp"

RedisMgr::RedisMgr()
    : m_redis([]() {
          auto& g_cfg = ConfigMgr::GetInstance();
          std::string host = g_cfg["Redis"]["Host"];
          std::string port = g_cfg["Redis"]["Port"];
          std::string passwd = g_cfg["Redis"]["Passwd"];
          std::string connection_str = "tcp://" + passwd + "@" + host + ":" + port;
          return sw::redis::Redis(connection_str);
      }()) {
}

bool RedisMgr::Get(const std::string& key, std::string& value) {
    auto val = m_redis.get(key);
    if (val) {
        value = *val;
        return true;
    }
    return false;
}

bool RedisMgr::Set(const std::string& key, const std::string& value) {
    m_redis.set(key, value);
    return true;
}

bool RedisMgr::SetEx(const std::string& key, const std::string& value, long long seconds) {
    m_redis.setex(key, std::chrono::seconds(seconds), value);
    return true;
}

bool RedisMgr::ExistsKey(const std::string& key) {
    return m_redis.exists(key) > 0;
}

bool RedisMgr::Del(const std::string& key) {
    return m_redis.del(key) > 0;
}
