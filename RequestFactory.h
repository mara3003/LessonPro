#pragma once
#include "IRequest.h"
#include <string>

using namespace std;
class RequestFactory
{
public:
	static IRequest* getRequest(string data);
};

