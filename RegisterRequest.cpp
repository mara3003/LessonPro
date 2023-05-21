#include "RegisterRequest.h"
#include "Header.h"


RegisterRequest::RegisterRequest(string data)
{
	vector<string> userDetails;//username, parola, nume, prenume,email, scoala, clasa
	userDetails=myStrtok(data);
	user = new User(userDetails[1],userDetails[2],userDetails[3],userDetails[4],userDetails[5],userDetails[6],stoi(userDetails[7]));
}

void RegisterRequest::makeRequest()
{
	int rez =DB::getInstance()->createUser(*this->user);
	if (rez  == 0)
	{
		this->answer = "ERR";
		cout << "ERR" << endl;
	}
	else {
		this->answer = "OK";
		cout << "OK" << endl;
	}
}

string RegisterRequest::sendResponse()
{
	return this->answer;
}
