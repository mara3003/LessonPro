#include "AllStudentsLessonRequest.h"
#include "Header.h"
#include "DB.h"
AllStudentsLessonRequest::AllStudentsLessonRequest(std::string data)
{
	std::vector<std::string> details;
	details = myStrtok(data);
	this->username = details[1];
}

void AllStudentsLessonRequest::makeRequest()
{
	this->lessons = DB::getInstance()->getAllStudentLesson(this->username);
	this->answer = VectorToString(lessons);
	
}

string AllStudentsLessonRequest::sendResponse()
{
	
	return this->answer;
}
