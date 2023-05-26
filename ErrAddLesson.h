#pragma once
#include "IException.h"
class ErrAddLesson : public IException
{
public:
	std::string printErr();
};

