#pragma once
#include "IRequest.h"
#include "Teacher.h"

class AddTeacherRequest : public IRequest
{
private:
	Teacher* teacher;
	string answer;

public:
	AddTeacherRequest(string data);
	void makeRequest();
	string sendResponse();
	~AddTeacherRequest() {}
};

