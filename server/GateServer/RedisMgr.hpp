#pragma once

#include <string>
#include <sw/redis++/redis++.h>

#include "Singleton.hpp"

class RedisMgr : public Singleton<RedisMgr> {
    friend class Singleton<RedisMgr>;

public:
    bool Get(const std::string& key, std::string& value);
    bool Set(const std::string& key, const std::string& value);
    bool SetEx(const std::string& key, const std::string& value, long long seconds);
    bool ExistsKey(const std::string& key);
    bool Del(const std::string& key);

private:
    RedisMgr();

    sw::redis::Redis m_redis;
};
