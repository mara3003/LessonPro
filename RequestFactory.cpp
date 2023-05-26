#include "RequestFactory.h"
#include "LoginRequest.h"
#include "RegisterRequest.h"
#include "AddTeacherRequest.h"
#include "RequestLesson.h"
#include "GetTeachersBySubjectRequest.h"
#include "GetAllSubjectRequest.h"
#include "GetFreeHoursByDataRequest.h"
#include "GetUserDetailsRequest.h"
#include "AllStudentsLessonRequest.h"
#include "AllLessonsAdminRequest.h"
#include "UpdateLessonRequest.h"
#include "DeleteLessonAdminRequest.h"

IRequest* RequestFactory::getRequest(string data)
{

    switch (data[0]) {
    case '0':
        return new RegisterRequest(data);//inregistrare
    case '1':
        return new LoginRequest(data);//logare
    case '2':
        return new AddTeacherRequest(data);//adaugare profesor
    case '3':
        return new RequestLesson(data);//programare meditatie
    case '4':
        return new GetTeachersBySubjectRequest(data);//...
    case '5':
        return new GetAllSubjectRequest();//toate materiile disponibile
    case '6':
        return new GetFreeHoursByDataRequest(data);//orele disponibile
    case '7':
        return new GetUserDetailsRequest(data);//detalii cont
    case '8':
        return new AllStudentsLessonRequest(data);//toate meditatiile unui student
    case '9':
        return new AllLessonsAdminRequest();//toate meditatiile pt admin
    case 'a':
        return new UpdateLessonRequest(data);//modificare meditatie
    case 'b':
        return new DeleteLessonAdminRequest(data);//stergere meditatie

    }
    return nullptr;
}
