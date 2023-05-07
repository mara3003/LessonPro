#pragma once

#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <nanodbc.h>
#include "User.h"
#include <vector>
#include <iostream>


class DB {
private:
    nanodbc::connection conn;
    static DB* instance;
   
    DB(const std::string connectionString) : conn(connectionString) {}

    ~DB() {};
public:
   
    //static DB* instance;
    void disconnect();

    static DB* getInstance();

    bool createUser( User& user);
    bool verifyUserByUsernamePassword(std::string username, std::string password);
    bool userDetails(const User& user) {};
    User getUserById(int id);
    bool updateUser( User& user);
    bool deleteUser(int id);
    std::vector<User> getUsersByEmail(const std::string& email);
};



