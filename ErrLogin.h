#pragma once
#include "IException.h"
class ErrLogin : public IException
{
public:
	std::string printErr();
};

