#include "DeleteLessonAdminRequest.h"
#include "Header.h"
#include "DB.h"

DeleteLessonAdminRequest::DeleteLessonAdminRequest(std::string data)
{
	std::vector<std::string> details;
	details = myStrtok(data);
	this->IDLesson = stoi(details[1]);
}

void DeleteLessonAdminRequest::makeRequest()
{
	this->answer = DB::getInstance()->deleteLesson(this->IDLesson);
	if (this->answer != "ERR") {
		JournalActions* action = new JournalActions("A lesson was successfully deleted.\n");
		writeActionsFile(action);
		delete action;
	}
}

string DeleteLessonAdminRequest::sendResponse()
{
	return this->answer;
}
