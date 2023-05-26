#pragma once
#include <string>
#include <iostream>
#include "JournalActions.h"


using namespace std;
using namespace std;
class IRequest
{
public:
	virtual void makeRequest() = 0;
	virtual string sendResponse() = 0;
	
};

