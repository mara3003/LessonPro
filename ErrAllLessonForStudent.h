#pragma once
#include "IException.h"
class ErrAllLessonForStudent : public IException
{
	std::string printErr();
};

