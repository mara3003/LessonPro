#include "GetUserDetailsRequest.h"
#include <vector>
#include "Header.h"
#include "DB.h"

GetUserDetailsRequest::GetUserDetailsRequest(std::string data)
{
	std::vector<std::string> details = myStrtok(data);
	this->username = details[1];
}

void GetUserDetailsRequest::makeRequest()
{
	this->answer = VectorToString(DB::getInstance()->getUserDetails(this->username));
	if (this->answer == "/ERR")
		this->answer = "ERR";

}

string GetUserDetailsRequest::sendResponse()
{
	return this->answer;
}
