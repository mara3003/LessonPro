#pragma once
#include "IException.h"
#include <string>

using namespace std;
class ExceptionFactory
{
public:
	static IException* getErr(int errCode);
};
