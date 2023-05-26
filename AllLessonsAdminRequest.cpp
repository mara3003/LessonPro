#include "AllLessonsAdminRequest.h"
#include "DB.h"
#include "Header.h"

void AllLessonsAdminRequest::makeRequest()
{
	this->answer = VectorToString(DB::getInstance()->getAllLessonsAdmin());
	if (this->answer != "/ERR")
	{
		JournalActions* action = new JournalActions("All lessons successfully requested by ADMIN.\n");
		writeActionsFile(action);
		delete action;
	}
}

string AllLessonsAdminRequest::sendResponse()
{

	return this->answer;
}
