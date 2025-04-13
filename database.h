#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <mysql/mysql.h>

class Database {
public:
    Database();
    ~Database();

    bool authenticateUser(const std::string &username, const std::string &password);
    bool registerUser(const std::string &username, const std::string &password, const std::string &email);

private:
    void connectToDatabase();
    MYSQL* conn; // MySQL connection pointer.
};

#endif // DATABASE_H