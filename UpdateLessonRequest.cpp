#include "UpdateLessonRequest.h"
#include <vector>
#include "Header.h"
#include "DB.h"

UpdateLessonRequest::UpdateLessonRequest(std::string data)
{
	std::vector<std::string> details;
	details = myStrtok(data);
	this->IDLesson = stoi(details[1]);
	this->date = details[2];
	this->time = details[3];
}

void UpdateLessonRequest::makeRequest()
{
	this->answer = DB::getInstance()->updateLessson(this->IDLesson,this->date,this->time);
	if (this->answer != "ERR") {
		JournalActions* action = new JournalActions("Lesson updated successfully.\n");
		writeActionsFile(action);
		delete action;
	}
}

string UpdateLessonRequest::sendResponse()
{
	return this->answer;
}
