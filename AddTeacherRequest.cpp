#include "AddTeacherRequest.h"
#include "DB.h"
#include "Header.h"


AddTeacherRequest::AddTeacherRequest(string data)
{
	vector<string> details;
	details=myStrtok(data);// 2/nume/prenume/email/materie/pret
	teacher = new Teacher(details[1], details[2], details[3], stoi(details[4]));
}

void AddTeacherRequest::makeRequest()
{
	int rez = DB::getInstance()->addTeacher(*teacher);
	if (rez == 0)
		answer = "ERR";
	else
		answer = "OK";
}

string AddTeacherRequest::sendResponse()
{
	return this->answer;
}
