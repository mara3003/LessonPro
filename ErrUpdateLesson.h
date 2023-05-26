#pragma once
#include "IException.h"
class ErrUpdateLesson : public IException
{
public:
	std::string printErr();
};

