#pragma once


#define SMTP_SERVER "smtp.mail.yahoo.com"
#define SENDER "mara_avram30@yahoo.com"

#include <string>
class SendMail
{
private:
	int lessonID;
	std::string receiverAddr;
	std::string hour;
	std::string date;
	std::string subject;
	std::string teacherName;
	std::string studentName;

public:
	SendMail(int lessonID)
		: lessonID(lessonID) {}
	
	void initializeData();

	void send();

};

