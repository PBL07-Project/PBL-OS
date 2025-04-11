#include "db.h"
#include <iostream>

Database::Database() {
    conn = mysql_init(nullptr);
}

Database::~Database() {
    if (conn) {
        mysql_close(conn);
    }
}

bool Database::connect(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname, unsigned int port) {
    conn = mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
    return conn != nullptr;
}

MYSQL* Database::getConnection() {
    return conn;
}
