#pragma once
#include "IRequest.h"
class GetAllSubjectRequest : public IRequest
{
private:
	std::string answer;

public:
	GetAllSubjectRequest() { this->answer = ""; }
	void makeRequest();
	string sendResponse();

};

