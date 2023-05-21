#pragma once
#include "IRequest.h"
class GetFreeHoursByDataRequest : public IRequest
{
private:
	std::string answer;
	std::string TeacherName;
	std::string subject;
	std::string date;

public:
	GetFreeHoursByDataRequest(std::string data);
	void makeRequest();
	string sendResponse();
};

