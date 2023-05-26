#pragma once
#include "IRequest.h"
class UpdateLessonRequest : public IRequest
{
private:
	std::string date;
	std::string time;
	int IDLesson;
	std::string answer;

public:
	UpdateLessonRequest(std::string data);
	void makeRequest();
	string sendResponse();
};

