#pragma once
#include "IException.h"
class ErrGetSubjects : public IException
{
public:
	std::string printErr();
};

