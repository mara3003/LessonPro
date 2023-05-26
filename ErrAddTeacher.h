#pragma once
#include "IException.h"
class ErrAddTeacher : public IException
{
public:
	std::string printErr();
};

