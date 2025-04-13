#include "database.h"
#include <mysql/mysql.h>
#include <iostream>
#include <cstring>
#include <cstdlib>

Database::Database() : conn(nullptr) {
    connectToDatabase();
}

Database::~Database() {
    if(conn) {
        mysql_close(conn);
    }
}

void Database::connectToDatabase() {
    // Update these parameters with your MySQL configuration.
    const char* host = "sql12.freesqldatabase.com";
    const char* user = "sql12772615";
    const char* pass = "96Q3vgiAiB";
    const char* db   = "sql12772615";
    unsigned int port = 3306;
    
    conn = mysql_init(nullptr);
    if(!conn) {
        std::cerr << "mysql_init failed" << std::endl;
        exit(1);
    }
    
    if(!mysql_real_connect(conn, host, user, pass, db, port, nullptr, 0)) {
        std::cerr << "mysql_real_connect failed: " << mysql_error(conn) << std::endl;
        exit(1);
    }
}

bool Database::authenticateUser(const std::string &username, const std::string &password) {
    if(username.empty() || password.empty())
        return false;
    
    const char* query = "SELECT password FROM users WHERE username = ?";
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(!stmt)
        return false;
    
    if(mysql_stmt_prepare(stmt, query, std::strlen(query))) {
        mysql_stmt_close(stmt);
        return false;
    }
    
    MYSQL_BIND bindInput[1];
    std::memset(bindInput, 0, sizeof(bindInput));
    bindInput[0].buffer_type = MYSQL_TYPE_STRING;
    bindInput[0].buffer = (char*)username.c_str();
    bindInput[0].buffer_length = username.size();
    
    if(mysql_stmt_bind_param(stmt, bindInput)) {
        mysql_stmt_close(stmt);
        return false;
    }
    
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return false;
    }
    
    MYSQL_BIND bindResult[1];
    std::memset(bindResult, 0, sizeof(bindResult));
    char storedPassword[256];
    unsigned long storedPasswordLength = 0;
    bindResult[0].buffer_type = MYSQL_TYPE_STRING;
    bindResult[0].buffer = storedPassword;
    bindResult[0].buffer_length = sizeof(storedPassword);
    bindResult[0].length = &storedPasswordLength;
    
    if(mysql_stmt_bind_result(stmt, bindResult)) {
        mysql_stmt_close(stmt);
        return false;
    }
    
    bool authSuccess = false;
    if(mysql_stmt_fetch(stmt) == 0) {
        storedPassword[storedPasswordLength] = '\0';
        if(password == std::string(storedPassword))
            authSuccess = true;
    }
    
    mysql_stmt_close(stmt);
    return authSuccess;
}

bool Database::registerUser(const std::string &username, const std::string &password, const std::string &email) {
    if(username.empty() || password.empty() || email.empty())
        return false;
    
    const char* query = "INSERT INTO users (username, password, email) VALUES (?, ?, ?)";
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(!stmt)
        return false;
    
    if(mysql_stmt_prepare(stmt, query, std::strlen(query))) {
        mysql_stmt_close(stmt);
        return false;
    }
    
    MYSQL_BIND bindInput[3];
    std::memset(bindInput, 0, sizeof(bindInput));
    
    bindInput[0].buffer_type = MYSQL_TYPE_STRING;
    bindInput[0].buffer = (char*)username.c_str();
    bindInput[0].buffer_length = username.size();
    
    bindInput[1].buffer_type = MYSQL_TYPE_STRING;
    bindInput[1].buffer = (char*)password.c_str();
    bindInput[1].buffer_length = password.size();
    
    bindInput[2].buffer_type = MYSQL_TYPE_STRING;
    bindInput[2].buffer = (char*)email.c_str();
    bindInput[2].buffer_length = email.size();
    
    if(mysql_stmt_bind_param(stmt, bindInput)) {
        mysql_stmt_close(stmt);
        return false;
    }
    
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return false;
    }
    mysql_stmt_close(stmt);
    return true;
}