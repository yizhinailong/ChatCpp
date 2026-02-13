#include "MySQLDao.hpp"

#include <iostream>

#include "ConfigMgr.hpp"

MySQLDao::MySQLDao() {
    auto& g_cfg = ConfigMgr::GetInstance();
    const auto& host = g_cfg["Mysql"]["Host"];
    const auto& port = g_cfg["Mysql"]["Port"];
    const auto& pwd = g_cfg["Mysql"]["Passwd"];
    const auto& schema = g_cfg["Mysql"]["Schema"];
    const auto& user = g_cfg["Mysql"]["User"];
    m_pool.reset(new MySqlPool(host, port, user, pwd, schema, 5));
}

MySQLDao::~MySQLDao() {
    m_pool->Close();
}

int MySQLDao::RegUser(const std::string& name, const std::string& email, const std::string& pwd) {
    auto session = m_pool->GetConnection();
    try {
        if (session == nullptr) {
            m_pool->ReturnConnection(std::move(session));
            return -1;
        }

        // 使用 X DevAPI 执行存储过程
        session->sql("CALL reg_user(?,?,?,@result)")
            .bind(name, email, pwd)
            .execute();

        // 获取存储过程的输出参数
        mysqlx::RowResult resultSet = session->sql("SELECT @result AS result").execute();
        if (resultSet.count() > 0) {
            mysqlx::Row row = resultSet.fetchOne();
            int result = row[0].get<int>();
            std::cout << "Result: " << result << std::endl;
            m_pool->ReturnConnection(std::move(session));
            return result;
        }
        m_pool->ReturnConnection(std::move(session));
        return -1;
    } catch (const mysqlx::Error& e) {
        m_pool->ReturnConnection(std::move(session));
        std::cerr << "MySQL Error: " << e.what();
        return -1;
    } catch (const std::exception& e) {
        m_pool->ReturnConnection(std::move(session));
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
}
