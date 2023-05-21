#include "SendMail.h"
#include "DB.h"

#include <iostream>
#include <string>
#include <memory>
#include <C:/Users/HOME/source/repos/POO_PROIECT-server-init/packages/Aspose.Email.Cpp.23.4.0/build/native/include/Aspose.Email.Cpp/Clients/Smtp/SmtpClient/SmtpClient.h>
#include <C:/Users/HOME/source/repos/POO_PROIECT-server-init/packages/Aspose.Email.Cpp.23.4.0/build/native/include/Aspose.Email.Cpp/MailMessage.h>
#include <C:/Users/HOME/source/repos/POO_PROIECT-server-init/packages/Aspose.Email.Cpp.23.4.0/build/native/include/Aspose.Email.Cpp/AlternateView.h>
#include <C:/Users/HOME/source/repos/POO_PROIECT-server-init/packages/Aspose.Email.Cpp.23.4.0/build/native/include/Aspose.Email.Cpp/LinkedResource.h>
#include <C:/Users/HOME/source/repos/POO_PROIECT-server-init/packages/Aspose.Email.Cpp.23.4.0/build/native/include/Aspose.Email.Cpp/MailAddressCollection.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object_ext.h>
#include <system/object.h>
#include <system/exceptions.h>
#include <system/diagnostics/trace.h>
#include <system/console.h>

using namespace Aspose::Email;
using namespace Aspose::Email::Clients::Smtp::Commands;
using namespace Aspose::Email::Clients::Smtp;
using namespace Aspose::Email::Clients::Smtp::Models;
//using namespace Aspose::Email::
using namespace std;


void SendMail::initializeData()
{
	std::vector<std::string> details;
	details = DB::getInstance()->getLessonDetailsForMail(this->lessonID);
	this->teacherName = details[0];
	this->studentName = details[1];
	this->receiverAddr = details[2];
	this->date = details[3];
	this->hour = details[4];
}

void SendMail::send() {
    

}

