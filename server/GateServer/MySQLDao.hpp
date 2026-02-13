#pragma once

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include <mysqlx/xdevapi.h>

#include "Const.hpp"

class MySqlPool {
public:
    MySqlPool(const std::string& host,
              const std::string& port,
              const std::string& user,
              const std::string& passwd,
              const std::string& schema,
              int pool_size = 10)
        : m_host(host),
          m_port(port),
          m_user(user),
          m_passwd(passwd),
          m_schema(schema),
          m_pool_size(pool_size),
          m_b_stop(false) {
        try {
            // 构建连接 URI，使用传统 SQL 模式（兼容性更好）
            std::string uri = "mysqlx://" +
                              m_user + ":" +
                              m_passwd + "@" +
                              m_host + ":" +
                              m_port + "?x-protocol=false";

            for (int i = 0; i < m_pool_size; ++i) {
                std::unique_ptr<mysqlx::Session> session(new mysqlx::Session(uri));
                session->sql("USE " + m_schema).execute();
                m_pool.push(std::move(session));
            }
        } catch (const mysqlx::Error& e) {
            std::cout << "MySQL pool init failed: " << e.what() << std::endl;
        }
    }

    std::unique_ptr<mysqlx::Session> GetConnection() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this] {
            if (m_b_stop) {
                return true;
            }
            return !m_pool.empty();
        });
        if (m_b_stop) {
            return nullptr;
        }
        std::unique_ptr<mysqlx::Session> session(std::move(m_pool.front()));
        m_pool.pop();
        return session;
    }

    void ReturnConnection(std::unique_ptr<mysqlx::Session> session) {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_b_stop) {
            return;
        }
        m_pool.push(std::move(session));
        m_condition.notify_one();
    }

    void Close() {
        m_b_stop = true;
        m_condition.notify_all();
    }

    ~MySqlPool() {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (!m_pool.empty()) {
            m_pool.pop();
        }
    }

private:
    std::string m_host;
    std::string m_port;
    std::string m_user;
    std::string m_passwd;
    std::string m_schema;
    int m_pool_size;
    std::queue<std::unique_ptr<mysqlx::Session>> m_pool;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::atomic<bool> m_b_stop;
};

class MySQLDao {
public:
    MySQLDao();
    ~MySQLDao();
    int RegUser(const std::string& name, const std::string& email, const std::string& passwd);

private:
    std::unique_ptr<MySqlPool> m_pool;
};
