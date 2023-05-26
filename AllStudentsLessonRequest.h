#pragma once
#include "IRequest.h"
#include <vector>
class AllStudentsLessonRequest : public IRequest
{
private:
	std::string username;
	std::vector<std::string> lessons;
	std::string answer;

public:
	AllStudentsLessonRequest(std::string data);
	void makeRequest();
    string sendResponse();

};

