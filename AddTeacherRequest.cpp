#include "AddTeacherRequest.h"
#include "DB.h"
#include "Header.h"


AddTeacherRequest::AddTeacherRequest(string data)
{
	vector<string> details;
	details=myStrtok(data);// 2/nume/prenume/materie/pret
	teacher = new Teacher(details[1], details[2], details[3], stoi(details[4]));
}

void AddTeacherRequest::makeRequest()
{
	bool rez = DB::getInstance()->addTeacher(*teacher);
	if (rez == false)
		answer = "ERR";
	else {
		answer = "OK";
		JournalActions* action = new JournalActions("Teacher added successfully.\n");
		writeActionsFile(action);
		delete action;
	}
}

string AddTeacherRequest::sendResponse()
{
	return this->answer;
}
