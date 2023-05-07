#include "RequestFactory.h"
#include "LoginRequest.h"
#include "RegisterRequest.h"


IRequest* RequestFactory::getRequest(string data)
{
    switch (data[0]) {
    case '0':
        return new RegisterRequest(data);//inregistrare
    case '1':
        return new LoginRequest(data);//logare


    }
    return nullptr;
}
