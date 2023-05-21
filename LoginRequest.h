#pragma once
#include "IRequest.h"


class LoginRequest : public IRequest
{
private:
	std::string username;
	std::string password;
	std::string answer;

public:
	LoginRequest(string);
	~LoginRequest() {}

	void makeRequest() override;
	string sendResponse() override;
};

