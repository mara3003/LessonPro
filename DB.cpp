
#include "DB.h"
#include <exception>
#include <nanodbc/nanodbc.h>
#include "Header.h"
#include "ExceptionFactory.h"
#include <fstream>
#include <time.h>

DB* DB::instance = nullptr;

bool DB::createUser(User& user) {
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
                INSERT INTO Students([Username],[Password],[E-mail],[LastName],[FirstName],[School],[Grade]) 
                VALUES (?,HASHBYTES('SHA2_512',?),?,?,?,?,?);
        )");
        
        const std::string w1 = user.getUsername();
        const std::string w2 = user.getPassword();
        const std::string w3 = user.getEmail();
        const std::string w4 = user.getlastName();
        const std::string w5 = user.getfirstName();
        const std::string w6 = user.getschoolName();
        stmt.bind(0, w1.c_str());
        stmt.bind(1, w2.c_str());
        stmt.bind(2, w3.c_str());
        stmt.bind(3, w4.c_str());
        stmt.bind(4, w5.c_str());
        stmt.bind(5, w6.c_str());
        const int grade = user.getGrade();
        stmt.bind(6, &grade);
        nanodbc::result rez = stmt.execute();

        if (rez.affected_rows() == 0)
        {
            throw ExceptionFactory::getErr(3);
        }
        else
            return true;
    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        return false;
    }

}

bool DB::addTeacher(Teacher& teacher)
{
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
                INSERT INTO Teachers([LastName],[FirstName],[Subject],[Lesson price]) 
                VALUES (?,?,?,?);
        )");

        const std::string w1 = teacher.getLastName();
        const std::string w2 = teacher.getFirstName();
        const std::string w4 = teacher.getSubject();
        const int w5 = teacher.getPrice();
        stmt.bind(0, w1.c_str());
        stmt.bind(1, w2.c_str());
        stmt.bind(2, w4.c_str());
        stmt.bind(3, &w5);

        nanodbc::result rez = stmt.execute();
        if (rez.affected_rows() == 0)
        {
            throw ExceptionFactory::getErr(2);
        }
        else
            return true;
    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        return false;
    }

   
}

int DB::verifyUserByUsernamePassword(std::string username, std::string password)
{
    try {
        if (username == "admin" && password == "admin")
            return -1;

        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            SELECT Username, Password FROM Students 
            WHERE Username=? AND Password=HASHBYTES('SHA2_512',?) ;
        )");


        stmt.bind(0, username.c_str());
        stmt.bind(1, password.c_str());

        nanodbc::result rez = stmt.execute();

        if (rez.affected_rows() == 0)
        {
            throw ExceptionFactory::getErr(1);
        }
        else
            return true;
    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        return false;
    }
}

bool DB::addLesson(std::string Teacher, std::string usernameStud, std::string date, std::string timeT)
{
    try {
        if (Teacher == "" || usernameStud == "" || date == "" || timeT == "") {
            throw ExceptionFactory::getErr(4);
        }
        std::string IDTeacher = this->getTeacherByName(Teacher);
        std::string IDstud = this->getStudentByUsername(usernameStud);
        if (IDTeacher == "ERR" || IDstud == "ERR")
            return false;


        nanodbc::statement stmt3(conn);
        nanodbc::prepare(stmt3, R"(
            INSERT INTO Lessons(IDTeacher,IDStudent,[Date], [Time]) VALUES
            (?,?,?,?);
        )");

        int ID1 = stoi(IDTeacher);
        int ID2 = stoi(IDstud);
        stmt3.bind(0, &ID1);
        stmt3.bind(1, &ID2);
        stmt3.bind(2, date.c_str());
        stmt3.bind(3, timeT.c_str());
        nanodbc::result rez3 = stmt3.execute();
        if (rez3.affected_rows() == 0)
        {
            throw ExceptionFactory::getErr(4);
        }
        else
            return true;
    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        return false;
    }

}

std::string DB::getTeacherByName(std::string Teacher)
{
    try {
        nanodbc::statement stmt1(conn);
        nanodbc::prepare(stmt1, R"(
            SELECT IDTeacher FROM Teachers 
            WHERE LastName = ? AND FirstName = ? ;
        )");

        std::vector<std::string> teacher = myStrtok2(Teacher);
        const std::string w1 = teacher[0];
        const std::string w2 = teacher[1];
        stmt1.bind(0, w1.c_str());
        stmt1.bind(1, w2.c_str());

        nanodbc::result rez1 = stmt1.execute();
        if (rez1.affected_rows() == 0)
            return "ERR";
        rez1.next();
        std::string IDteacher = rez1.get<std::string>(0);

        return IDteacher;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err.what();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        return "ERR";
    }
}

std::string DB::getStudentByUsername(std::string username)
{
    try {
        nanodbc::statement stmt2(conn);
        nanodbc::prepare(stmt2, R"(
            SELECT IDStudent FROM Students 
            WHERE username = ? ;
        )");

        stmt2.bind(0, username.c_str());
        nanodbc::result rez2 = stmt2.execute();
        rez2.next();
        std::string IDStud = rez2.get<std::string>(0);

        if (rez2.affected_rows() != 0)
             return IDStud;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err.what();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        return "ERR";
    }
}

std::vector<std::string> DB::getAllTeachersBySubject(std::string subject)
{
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
        SELECT LastName, FirstName 
        FROM Teachers 
        WHERE Subject=?;
    )");
        const std::string subj = subject;
        stmt.bind(0, subj.c_str());
        nanodbc::result result = stmt.execute();

        int num_columns = result.columns();
        vector<string> teachers;
        if (result.affected_rows() == 0)
        {
            
            throw ExceptionFactory::getErr(5);
            
        }

        while (result.next()) {
            for (int i = 0; i < num_columns; i++) {
                std::string Lname;
                Lname = result.get<string>(i);
                my_deleteBlank(Lname);
                i++;
                std::string Fname;
                Fname = result.get<string>(i);
                Lname = Lname + " " + my_deleteBlank(Fname);
                teachers.push_back(Lname);
            }
        }

        return teachers;
    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        vector<string> teachers;
        teachers.push_back("ERR");
        return teachers;
    }
}

std::vector<std::string> DB::getAllSubjects()
{
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
        SELECT DISTINCT [Subject]
        FROM Teachers 
    )");

        nanodbc::result result = stmt.execute();

        int num_columns = result.columns();
        vector<string> subjects;
        if (result.affected_rows() == 0)
        {
            throw ExceptionFactory::getErr(6);
        }

        while (result.next()) {
            std::string subj;
            subj = result.get<string>(0);
            my_deleteBlank(subj);
            subjects.push_back(subj);

        }

        return subjects;
    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        vector<string> subjects;
        subjects.push_back("ERR");
        return subjects;
    }
   
}

std::vector<std::string> DB::getFreeHoursTeacher(std::string TeacherName, std::string subject, std::string date)
{
    try {
        std::string IDteacher;
        IDteacher = this->getTeacherByName(TeacherName);
        //if(ID)
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
        SELECT [Time]
        FROM Lessons
        WHERE IDTeacher = ? AND [Date] = ? ;
    )");

        const std::string ID = IDteacher;
        const std::string D = date;
        stmt.bind(0, ID.c_str());
        stmt.bind(1, D.c_str());

        nanodbc::result result = stmt.execute();

       

        int num_columns = result.columns();
        std::vector<std::string> timeV = { "08:00","10:00","12:00","16:00","18:00" };
        if (result.affected_rows() == 5)
        {
            timeV.clear();
            timeV.push_back("ERR");
            return timeV;
        }

        if (result.rowset_size() == 0) {
            return timeV;
        }
        
        while (result.next()) {
            for (int i = 0; i < num_columns; i++) {
                std::string timeB;
                timeB = result.get<string>(i);
                my_deleteBlank(timeB);
                auto result = std::find(timeV.begin(), timeV.end(), timeB);
                timeV.erase(result);
            }
        }

        return timeV;
    }
    catch (nanodbc::database_error err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err.what();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        vector<string> subjects;
        subjects.push_back("ERR");
        return subjects;
    }
}

std::vector<std::string> DB::getUserDetails(std::string username)
{
    try {
        if (username == "")
            throw ExceptionFactory::getErr(7);
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            SELECT LastName, FirstName, [E-mail],School,Grade
            FROM Students 
            WHERE Username=? ;
        )");

        const std::string user = username;
        stmt.bind(0, user.c_str());
        nanodbc::result result = stmt.execute();

        std::vector<std::string> details;
        int num_columns = result.columns();

        if (result.rowset_size() == 0) {
            throw ExceptionFactory::getErr(7);
        }

        while (result.next()) {
            for (int i = 0; i < num_columns; i++) {
                std::string word;
                word = result.get<string>(i);
                my_deleteBlank(word);
                details.push_back(word);
            }
        }

        return details;
    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        vector<string> details;
        details.push_back("ERR");
        return details;
    }

}

std::vector<std::string> DB::getLessonDetailsForMail(int lessonID)
{
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
        SELECT IDTeacher,IDStudent,[Date],[Time]
        FROM Lessons
        WHERE IDLesson = ?;
    )");

        stmt.bind(0, &lessonID);

        nanodbc::result result = stmt.execute();

        std::vector<std::string> details;
        //int num_columns = result.columns();

        if (result.rowset_size() == 0) {
            details.push_back("ERR");
            return details;
        }

        while (result.next()) {
            int TID;
            TID = result.get<int>(0);
            std::vector<std::string> Tdet = this->getTeacherByID(TID);
            details.push_back(Tdet[0]);//teacher name

            int SID;
            SID = result.get<int>(1);
            std::vector<std::string> V;
            V = this->getStudentByID(SID);
            details.push_back(V[0]);//student name
            details.push_back(V[1]);//student email

            std::string word;
            word = result.get<string>(2);
            my_deleteBlank(word);
            details.push_back(word);//data

            word = result.get<string>(3);
            my_deleteBlank(word);
            details.push_back(word);//ora

            details.push_back(Tdet[1]);//subject

        }
        return details;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err.what();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        std::vector<std::string> details;
        details.push_back("ERR");
        return details;
    }
}

std::vector<std::string> DB::getStudentByID(int ID)
{
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            SELECT LastName, FirstName, [E-mail]
            FROM Students 
            WHERE IDStudent=? ;
        )");

        stmt.bind(0, &ID);

        nanodbc::result result = stmt.execute();

        std::vector<std::string> details;

        if (result.rowset_size() == 0) {
            details.push_back("ERR");
            return details;
        }

        while (result.next()) {

            std::string FName, Lname;
            FName = result.get<string>(0);
            my_deleteBlank(FName);

            Lname = result.get<string>(1);
            my_deleteBlank(Lname);

            FName = FName + " " + Lname;
            details.push_back(FName);

            std::string email;
            email = result.get<string>(2);
            my_deleteBlank(email);
            details.push_back(email);

        }

        return details;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err.what();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        std::vector<std::string> details;
        details.push_back("ERR");
        return details;
    }
}

std::vector<std::string> DB::getTeacherByID(int ID)
{
    try{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            SELECT LastName, FirstName,[Subject]
            FROM Teachers 
            WHERE IDTeacher=? ;
        )");

    stmt.bind(0, &ID);

    nanodbc::result result = stmt.execute();

    std::vector<std::string> details;

    if (result.rowset_size() == 0) {
        details.push_back("ERR");
        return details;
    }

    std::string FName, Lname;
    while (result.next()) {

        
        FName = result.get<string>(0);
        my_deleteBlank(FName);

        Lname = result.get<string>(1);
        my_deleteBlank(Lname);

        FName = FName + " " + Lname;
        details.push_back(FName);

        std::string subj = result.get<string>(2);
        my_deleteBlank(subj);
        details.push_back(subj);

    }

    return details;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err.what();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        std::vector<std::string> details;
        details.push_back("ERR");
        return details;
    }
}

std::vector<int> DB::getTomorrowLessons(tm* ltm)
{
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            SELECT IDLesson
            FROM Lessons 
            WHERE [Date]=? ;
        )");
        // if(ltm->tm_mday==31 && (ltm->tm_mon)
        std::string date = to_string(ltm->tm_year) + "-" + to_string(ltm->tm_mon) + "-" + to_string(ltm->tm_mday + 1);
        if (ltm->tm_mon <= 9)
            date.insert(5, "0");
        if (ltm->tm_mday <= 9)
            date.insert(8, "0");


        stmt.bind(0, date.c_str());

        nanodbc::result result = stmt.execute();
        std::vector<int> lessons;

        if (result.rowset_size() == 0) {
            lessons.push_back(-1);
            return lessons;
        }

        while (result.next()) {
            int ID;
            ID = result.get<int>(0);
            lessons.push_back(ID);
        }
        return lessons;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err.what();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        std::vector<int> lessons;
        lessons.push_back(-1);
        return lessons;
    }
}

std::vector<std::string> DB::getAllStudentLesson(std::string username)
{
    try {
        if (username == "")
        {
            throw ExceptionFactory::getErr(10);
        }
        int IDStudent = stoi(this->getStudentByUsername(username));
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
        SELECT Teachers.FirstName AS FN ,Teachers.LastName AS LN,[Date],[Time],Teachers.[Subject]
        FROM Lessons
        INNER JOIN Teachers ON Lessons.IDTeacher=Teachers.IDTeacher
        WHERE IDStudent = ?;
    )");

        stmt.bind(0, &IDStudent);

        nanodbc::result result = stmt.execute();

        std::vector<std::string> details;

        if (result.affected_rows() == 0) {
            details.push_back("ERR");
            return details;
        }

        while (result.next()) {

            std::string firstName = result.get<string>(0);
            my_deleteBlank(firstName);
            std::string lastName = result.get<string>(1);
            my_deleteBlank(lastName);
            firstName = firstName + " " + lastName;
            details.push_back(firstName);//teacher name

            std::string word;
            for (int i = 2; i < 5; i++) {
                word = result.get<string>(i);
                my_deleteBlank(word);
                details.push_back(word);
            }

        }
        return details;
    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        std::vector<std::string> v;
        v.push_back("ERR");
        return v;
    }

}

std::vector<std::string> DB::getAllLessonsAdmin()
{
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
        SELECT IDLesson,Students.LastName AS SFN,Students.FirstName AS SLN, Teachers.LastName AS TFN,Teachers.FirstName AS TLN,Teachers.[Subject],[Date],[Time]
        FROM Lessons
        INNER JOIN Students ON Students.IDStudent = Lessons.IDStudent
        INNER JOIN Teachers ON Teachers.IDTeacher = Lessons.IDTeacher
       
    )");

        nanodbc::result result = stmt.execute();
        std::vector<std::string> details;
        if (result.affected_rows() == 0) {
            details.push_back("NU EXITA MEDITATII");
            return details;
        }

        int num_col = result.columns();
        std::string word;
        while (result.next()) {
            for (int i = 0; i < num_col; i++)
            {
                word = result.get<string>(i);
                my_deleteBlank(word);
                if (i == 1 || i == 3) {

                    std::string word2 = result.get<string>(i + 1);
                    my_deleteBlank(word2);
                    word = word + " " + word2;
                    i++;
                }
                details.push_back(word);
            }
        }

        return details;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
        std::vector<std::string> details;
        details.push_back("NU EXITA MEDITATII");
        return details;
    }
}

std::string DB::updateLessson(int IDLesson, std::string date, std::string timeT)
{
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
        UPDATE Lessons
        SET [Date] = ? , [Time] = ?
        WHERE IDLesson = ?;
        
    )");

        const std::string w1 = date;
        const std::string w2 = timeT;
        const int w3 = IDLesson;
        stmt.bind(0, w1.c_str());
        stmt.bind(1, w2.c_str());
        stmt.bind(2, &w3);

        nanodbc::result result = stmt.execute();
       
        if (result.affected_rows() != 1) {
            throw ExceptionFactory::getErr(8);
        }
        else {
            return "OK";
        }

    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        return "ERR";
    }

    
}

std::string DB::deleteLesson(int IDLesson)
{
    try {

        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
        DELETE 
        FROM Lessons
        WHERE IDLesson = ?;
        
    )");

        const int w3 = IDLesson;
        stmt.bind(0, &w3);

        nanodbc::result result = stmt.execute();

        if (result.affected_rows() == 1) {
            return "OK";
        }
        else {
            throw ExceptionFactory::getErr(9);
        }
    }
    catch (IException* err) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += err->printErr();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        return "ERR";
    }

}


void DB::disconnect() {
    if (conn.connected()) {
        conn.disconnect();
        conn.deallocate();
    }

    if (instance != NULL)
        delete instance;
}

DB* DB::getInstance()
{
    if (instance == NULL)
        instance = new DB("Driver={ODBC Driver 17 for SQL Server};Server=LAPTOP-MARA;Database=LessonProDB;Trusted_Connection=yes;");
    return instance;
}
