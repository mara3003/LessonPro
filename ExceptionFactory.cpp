#include "ExceptionFactory.h"
#include "ErrLogin.h"
#include "ErrAddTeacher.h"
#include "ErrRegister.h"
#include "ErrAddLesson.h"
#include "ErrGetTeacher.h"
#include "ErrGetSubjects.h"
#include "ErrGetUserDetails.h"
#include "ErrUpdateLesson.h"
#include "ErrDeleteLesson.h"
#include "ErrAllLessonForStudent.h"

IException* ExceptionFactory::getErr(int errCode)
{
    switch (errCode) {
    case 1:
        return new ErrLogin();
    case 2:
        return new ErrAddTeacher();
    case 3:
        return new ErrRegister();
    case 4:
        return new ErrAddLesson();
    case 5:
        return new ErrGetTeacher();
    case 6:
        return new ErrGetSubjects();
    case 7:
        return new ErrGetUserDetails();
    case 8:
        return new ErrUpdateLesson();
    case 9:
        return new ErrDeleteLesson();
    case 10:
        return new ErrAllLessonForStudent();
    }
    return nullptr;
}
