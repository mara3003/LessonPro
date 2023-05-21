#include "GetAllSubjectRequest.h"
#include "DB.h"
#include "Header.h"

void GetAllSubjectRequest::makeRequest()
{
	this->answer = VectorToString(DB::getInstance()->getAllSubjects());
	if (answer == "/ERR")
		answer = "ERR";
	else
		this->answer = this->answer;
}

string GetAllSubjectRequest::sendResponse()
{
	return this->answer;
}
