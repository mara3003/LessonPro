#pragma once
#include "IException.h"
class ErrDeleteLesson : public IException
{
public:
	std::string printErr();
};

