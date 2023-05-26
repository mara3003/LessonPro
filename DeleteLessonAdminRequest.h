#pragma once
#include "IRequest.h"
class DeleteLessonAdminRequest : public IRequest
{
private:
	int IDLesson;
	std::string answer;

public:
	DeleteLessonAdminRequest(std::string data);
	void makeRequest();
	string sendResponse();
};

