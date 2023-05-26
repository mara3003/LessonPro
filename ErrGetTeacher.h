#pragma once
#include "IException.h"
class ErrGetTeacher : public IException
{
public:
	std::string printErr();
};

