#include "LoginRequest.h"
#include "DB.h"
#include "Header.h"


LoginRequest::LoginRequest(string data)
{
    vector<string> details;
    details=myStrtok(data);
    username = details[1];
    password = details[2];
}

void LoginRequest::makeRequest()
{
    try {
        int rez = DB::getInstance()->verifyUserByUsernamePassword(this->username, this->password);
        cout << rez<<endl;
        if (rez==0)
            answer = "ERR";
        else {
            if (rez == -1)
                answer = "ADMIN";
            else
                answer = "OK";
            
        }
    }
    catch (nanodbc::database_error err) {
        cout << err.what()<<endl;
    }


}

string LoginRequest::sendResponse()
{
    return this->answer;
}
