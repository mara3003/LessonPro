#include "DB.h"
#include <exception>
#include <nanodbc/nanodbc.h>

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

        return rez.has_affected_rows();
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
    }

}

bool DB::verifyUserByUsernamePassword(std::string username, std::string password)
{
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
    else {
        return true;
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
    //cout << "\nDisplaying " << result.rowset_size() << " rows "
    //    << "(" << result.rowset_size() << " fetched at a time):" << endl;

    //// show the column names
    //cout << "row\t";
    //for (short i = 0; i < columns; ++i)
    //    cout << result.column_name(i) << "\t";
    //cout << endl;

    if (result.next()) {
        /*user.id = result.get<int>(0);
        user.username = result.get<std::string>(1);
        user.email = result.get<std::string>(2);*/
    }

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


