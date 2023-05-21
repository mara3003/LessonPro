#pragma once
#include "IRequest.h"
class GetUserDetailsRequest : public IRequest
{
private:
	std::string answer;
	std::string username;

public:
	GetUserDetailsRequest(std::string data);
	void makeRequest();
	string sendResponse();
};

