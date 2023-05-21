#include "GetTeachersBySubjectRequest.h"
#include "Header.h"
#include "DB.h"

GetTeachersBySubjectRequest::GetTeachersBySubjectRequest(std::string data)
{
	this->subject = myStrtok(data)[1];
}

void GetTeachersBySubjectRequest::makeRequest()
{
	std::vector<std::string> teachers = DB::getInstance()->getAllTeachersBySubject(this->subject);
	this->answer = VectorToString(teachers);
	this->answer = this->answer;
}

string GetTeachersBySubjectRequest::sendResponse()
{
	return this->answer;
}
