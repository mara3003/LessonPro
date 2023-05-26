#pragma once
#include "IException.h"
class ErrRegister : public IException
{
public:
	std::string printErr();
};

