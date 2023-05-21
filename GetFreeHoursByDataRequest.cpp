#include "GetFreeHoursByDataRequest.h"
#include "Header.h"
#include "DB.h"

GetFreeHoursByDataRequest::GetFreeHoursByDataRequest(std::string data)
{
	std::vector<std::string> details = myStrtok(data);
	this->subject = details[1];
	this->TeacherName = details[2];
	this->date = details[3];
	
}

void GetFreeHoursByDataRequest::makeRequest()
{
	this->answer = VectorToString(DB::getInstance()->getFreeHoursTeacher(this->TeacherName, this->subject, this->date));
	
	if (answer == "/ERR")
		answer = "ERR";
	else
		this->answer = this->answer;
}

string GetFreeHoursByDataRequest::sendResponse()
{
	return this->answer;
}
