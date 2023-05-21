#pragma once
#include "IRequest.h"
class GetTeachersBySubjectRequest : public IRequest
{
private:
	std::string subject;
	std::string answer;

public:
	GetTeachersBySubjectRequest(std::string data);
	virtual void makeRequest();
	virtual string sendResponse();
};

