#pragma once
#include "IRequest.h"
#include "DB.h"

class RegisterRequest : public IRequest
{
private:
	User* user;
	string answer;

public:
	RegisterRequest(string data);
	void makeRequest();
	string sendResponse();
	
};

