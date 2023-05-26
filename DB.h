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
    int verifyUserByUsernamePassword(std::string username, std::string password);
    bool addLesson(std::string Teacher, std::string usernameStud, std::string date,std::string time);
    std::string getTeacherByName(std::string Teacher);
    std::string getStudentByUsername(std::string username);
    std::vector<std::string> getAllTeachersBySubject(std::string subject);
    std::vector<std::string> getAllSubjects();
    std::vector<std::string> getFreeHoursTeacher(std::string TeacherName,std::string subject,std::string date);
    std::vector<std::string> getUserDetails(std::string username);
    std::vector<std::string> getLessonDetailsForMail(int lessonID);
    std::vector<std::string> getStudentByID(int ID);
    std::vector<std::string> getTeacherByID(int ID);
    std::vector<int> getTomorrowLessons(tm* ltm);
    std::vector<std::string> getAllStudentLesson(std::string username);
    std::vector<std::string> getAllLessonsAdmin();
    std::string updateLessson(int IDLesson, std::string date, std::string time);
    std::string deleteLesson(int IDLesson);

   
};



