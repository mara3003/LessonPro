#pragma once
#include "IException.h"
class ErrGetUserDetails : public IException
{
public:
	std::string printErr();
};

