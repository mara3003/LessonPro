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

LoginRequest::~LoginRequest()
{
    this->answer = "";
    this->password = "";
    this->username = "";
}

void LoginRequest::makeRequest()
{
        int rez = DB::getInstance()->verifyUserByUsernamePassword(this->username, this->password);
       
        if (rez==0)
            answer = "ERR";
        else {
            if (rez == -1)
            {
                answer = "ADMIN";
                JournalActions* action = new JournalActions("ADMIN logged in.\n");
                writeActionsFile(action);
                delete action;
            }
            else {
                answer = "OK";
                JournalActions* action = new JournalActions("Student logged in.\n");
                writeActionsFile(action);
                delete action;
            }

            
        }
        cout << "Rezultatul functiei de logare: " << answer << endl;
}

string LoginRequest::sendResponse()
{
    return this->answer;
}
