#pragma once

#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <nanodbc.h>
#include <vector>
#include <iostream>

#include "User.h"
#include "Teacher.h"


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
    bool addTeacher(Teacher& teacher);
    bool verifyUserByUsernamePassword(std::string username, std::string password);
    bool addLesson(std::string Teacher, std::string usernameStud, std::string date,std::string time);
    std::string getTeacherByName(std::string Teacher);
    std::string getStudentByUsername(std::string username);
    std::vector<std::string> getAllTeachersBySubject(std::string subject);
    std::vector<std::string> getAllSubjects();
    std::vector<std::string> getFreeHoursTeacher(std::string TeacherName,std::string subject,std::string date);
    std::vector<std::string> getUserDetails(std::string username);
    std::vector<std::string> getLessonDetailsForMail(int lessonID);
    std::vector<std::string> getStudentByID(int ID);
    std::string getTeacherByID(int ID);
    std::vector<int> getTomorrowLessons(tm* ltm);

    //
    bool userDetails(const User& user) {};
    User getUserById(int id);
    bool updateUser( User& user);
    bool deleteUser(int id);
    std::vector<User> getUsersByEmail(const std::string& email);
};



