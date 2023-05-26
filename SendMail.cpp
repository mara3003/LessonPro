
#include "SendMail.h"
#include "DB.h"
#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <curl/curl.h>
#include <string>
#include <tchar.h>
#include "JournalActions.h"
#include "Header.h"
#include <Python.h>




void SendMail::initializeData()
{
    	
    std::vector<std::string> details;
    details = DB::getInstance()->getLessonDetailsForMail(this->lessonID);
    this->teacherName = details[0];
    this->studentName = details[1];
    this->receiverAddr = details[2];
    this->date = details[3];
    this->hour = details[4];
    this->subject = details[5];
   

}

void SendMail::send() {
  //construiesc comanda pt rularea scriptului
    std::string ARGS="";
   
    ARGS = "python SendGmail.py ";
    
    ARGS += this->receiverAddr + " ";
    ARGS += "\""+this->studentName+"\"" + " ";
    ARGS += "\""+this->date+"\"" + " ";
    ARGS += "\""+this->hour+"\"" + " ";
    ARGS += "\""+this->subject+"\"" + " ";
    ARGS += "\""+this->teacherName+ "\"";
    
   
    
    const char* args_cstr = ARGS.c_str();

    //trimit comanda in cmd
    int status=system(args_cstr);
    if (status == 0)
    {
        JournalActions* action = new JournalActions("Reminder email was sent successfully.\n");
        writeActionsFile(action);
        delete action;
    }
    
}


