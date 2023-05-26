#pragma once
#include <string>
class JournalActions
{
private:
	std::string message;

public:
	JournalActions(std::string message)
		:message(message) {}
	std::string printAction();
};

