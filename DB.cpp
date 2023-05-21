#include "DB.h"
#include <exception>
#include <nanodbc/nanodbc.h>
#include "Header.h"

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

        return rez.affected_rows();
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
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
        return rez.affected_rows();
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
    }

   
}

bool DB::verifyUserByUsernamePassword(std::string username, std::string password)
{
    if (username == "admin")
        return -1;

    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            SELECT Username, Password FROM Students 
            WHERE Username=? AND Password=HASHBYTES('SHA2_512',?) ;
        )");

    
    stmt.bind(0, username.c_str());
    stmt.bind(1, password.c_str());

    nanodbc::result rez = stmt.execute();

    std::cout << rez.affected_rows() << std::endl;
    if(rez.affected_rows()==0)
        return false;
    else
            return true;
}



bool DB::addLesson(std::string Teacher, std::string usernameStud, std::string date, std::string time)
{
    try {
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
        stmt3.bind(3, time.c_str());
        nanodbc::result rez3 = stmt3.execute();
        if (rez3.affected_rows() == 0)
            return false;
        else
            return true;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
    }

}

std::string DB::getTeacherByName(std::string Teacher)
{
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
    rez1.next();
    std::string IDteacher = rez1.get<std::string>(0);
   
    //////////////////////////////////////////////
    //int num_columns = rez1.columns();

    //while (rez1.next())
    //{
    //    for (int i = 0; i < num_columns; i++)
    //    {
    //        try
    //        {
    //            std::string value = rez1.get<std::string>(i);
    //            IDteacher = value;
    //            // Do something with the value
    //        }
    //        catch (const nanodbc::index_range_error& e)
    //        {
    //            // Handle the exception
    //            std::cerr << "Caught exception: " << e.what() << std::endl;
    //        }
    //    }
    //}
    /////////////////////////////////////////////
  
    if (rez1.affected_rows() == 0)
        return "ERR";
    return IDteacher;
}

std::string DB::getStudentByUsername(std::string username)
{
    nanodbc::statement stmt2(conn);
    nanodbc::prepare(stmt2, R"(
            SELECT IDStudent FROM Students 
            WHERE username = ? ;
        )");

    stmt2.bind(0, username.c_str());
    nanodbc::result rez2 = stmt2.execute();
    rez2.next();
    std::string IDStud = rez2.get<std::string>(0);

    if (rez2.affected_rows() == 0)
        return "ERR";

    return IDStud;
}

std::vector<std::string> DB::getAllTeachersBySubject(std::string subject)
{
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
        teachers.push_back("ERR");
        return teachers;
    }

    while (result.next()) {
        for (int i = 0; i < num_columns; i++) {
            std::string Lname;
            Lname = result.get<string>(i);
            deleteBlank(Lname);
            i++;
            std::string Fname;
            Fname = result.get<string>(i);
            Lname = Lname +" "+ deleteBlank(Fname);
            teachers.push_back(Lname);
        }
    }

    return teachers;
}

std::vector<std::string> DB::getAllSubjects()
{
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
        subjects.push_back("ERR");
        return subjects;
    }

    
    result.next();
    for (int i = 0; i < num_columns; i++) {
            std::string subj;
            subj = result.get<string>(i);
            deleteBlank(subj);
            subjects.push_back(subj);
    }

    return subjects;
   
}

std::vector<std::string> DB::getFreeHoursTeacher(std::string TeacherName, std::string subject, std::string date)
{
    try {
        std::string IDteacher;
        IDteacher = this->getTeacherByName(TeacherName);
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
        std::vector<std::string> time = { "08:00","10:00","12:00","16:00","18:00" };
        if (result.affected_rows() == 5)
        {
            time.clear();
            time.push_back("ERR");
            return time;
        }

        if (result.rowset_size() == 0) {
            return time;
        }
        
        while (result.next()) {
            for (int i = 0; i < num_columns; i++) {
                std::string timeB;
                timeB = result.get<string>(i);
                deleteBlank(timeB);
                auto result = std::find(time.begin(), time.end(), timeB);
                time.erase(result);
            }
        }

        return time;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
    }
}

std::vector<std::string> DB::getUserDetails(std::string username)
{
    try {
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
            details.push_back("ERR");
            return details;
        }

        while (result.next()) {
            for (int i = 0; i < num_columns; i++) {
                std::string word;
                word = result.get<string>(i);
                deleteBlank(word);
                details.push_back(word);
            }
        }

        return details;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
    }

}

std::vector<std::string> DB::getLessonDetailsForMail(int lessonID)
{
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
        details.push_back(this->getTeacherByID(TID));//teacher name

        int SID;
        SID = result.get<int>(1);
        std::vector<std::string> V;
        V = this->getStudentByID(SID);
        details.push_back(V[0]);//student name
        details.push_back(V[1]);//student email

        std::string word;
        word = result.get<string>(2);
        details.push_back(word);//data

        word = result.get<string>(3);
        details.push_back(word);//ora

    }
    return details;
}

std::vector<std::string> DB::getStudentByID(int ID)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            SELECT LastName, FirstName, [E-mail]
            FROM Students 
            WHERE StudentID=? ;
        )");

    stmt.bind(0, &ID);

    nanodbc::result result = stmt.execute();

    std::vector<std::string> details;

    if (result.rowset_size() == 0) {
        details.push_back("ERR");
        return details;
    }

    while (result.next()) {

         std::string FName,Lname;
         FName = result.get<string>(0);
         deleteBlank(FName);
          
         Lname = result.get<string>(1);
         deleteBlank(Lname);

         FName = FName + " " + Lname;
         details.push_back(FName);

         details.push_back(result.get<string>(2));
        
    }

    return details;
}

std::string DB::getTeacherByID(int ID)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            SELECT LastName, FirstName, [E-mail]
            FROM Students 
            WHERE StudentID=? ;
        )");

    stmt.bind(0, &ID);

    nanodbc::result result = stmt.execute();

    std::vector<std::string> details;

    if (result.rowset_size() == 0) {
        
        return "ERR";
    }

    std::string FName, Lname;
    while (result.next()) {

        
        FName = result.get<string>(0);
        deleteBlank(FName);

        Lname = result.get<string>(1);
        deleteBlank(Lname);

        FName = FName + " " + Lname;

    }

    return FName;
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
        const std::string date = to_string(ltm->tm_year) + "-" + to_string(ltm->tm_mon) + "-" + to_string(ltm->tm_mday + 1);
        
        stmt.bind(0, date.c_str());

        nanodbc::result result = stmt.execute();
        std::vector<int> lessons;
        while (result.next()) {
            int ID;
            ID = result.get<int>(0);
            lessons.push_back(ID);
        }
        return lessons;
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
    }
}



User DB::getUserById(int id) {
    User user;
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
        SELECT id, username, email FROM users WHERE id = ?;
    )");
    stmt.bind(0, &id);

    nanodbc::result result = stmt.execute();

    const short columns = result.columns();
   
    return user;
}

bool DB::updateUser(User& user) {
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            UPDATE users SET username = ?, email = ? WHERE id = ?;
        )");

    stmt.bind(0, user.getUsername().c_str());
    stmt.bind(1, user.getEmail().c_str());
    //stmt.bind(2, &user.id);

    nanodbc::result rez = stmt.execute();

    return rez.has_affected_rows();
}

bool DB::deleteUser(int id) {
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            DELETE FROM users WHERE id = ?;
        )");

    stmt.bind(0, &id);

    nanodbc::result rez = stmt.execute();

    return rez.has_affected_rows();
}

std::vector<User> DB::getUsersByEmail(const std::string& email)
{
    std::vector<User> users;
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            SELECT id, username, email FROM users WHERE email LIKE ?;
        )");

    std::string email_pattern = "%" + email + "%";
    stmt.bind(0, email_pattern.c_str());

    nanodbc::result result = stmt.execute();

    while (result.next()) {
        User user;
       /* user.id = result.get<int>(0);
        user.username = result.get<std::string>(1);
        user.email = result.get<std::string>(2);
        users.push_back(user);*/
    }

    return users;
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


