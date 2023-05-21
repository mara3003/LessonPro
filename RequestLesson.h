#pragma once
#include "IRequest.h"
class RequestLesson : public IRequest
{
private:
	string Teacher;
	string date;
	string time;
	string usernameStud;
	string answer;

public:
	RequestLesson(string data);
	void makeRequest();
	string sendResponse();
};

