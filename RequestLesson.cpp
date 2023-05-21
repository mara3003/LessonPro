#include "RequestLesson.h"
#include "Header.h"
#include "DB.h"

RequestLesson::RequestLesson(string data)
{
	vector<string> details;
	details = myStrtok(data);
	this->Teacher = details[1];
	this->usernameStud = details[2];
	this->date = details[3];
	this->time = details[4];
	
}

void RequestLesson::makeRequest()
{
	int rez = DB::getInstance()->addLesson(this->Teacher, this->usernameStud, this->date,this->time);
	if (rez == 0)
		this->answer = "ERR";
	else
		this->answer = "OK";
}

string RequestLesson::sendResponse()
{
	return this->answer;
}
