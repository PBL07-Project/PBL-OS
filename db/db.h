#ifndef DB_H
#define DB_H

#include <mysql.h>
#include <string>

class Database {
private:
    MYSQL* conn;
public:
    Database();
    ~Database();
    bool connect(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname, unsigned int port);
    MYSQL* getConnection();
};

#endif
