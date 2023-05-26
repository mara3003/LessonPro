#pragma once
#include "IRequest.h"
class AllLessonsAdminRequest : public IRequest
{
private:
	std::string answer;

public:
	AllLessonsAdminRequest() {};
	void makeRequest();
	string sendResponse();
};

