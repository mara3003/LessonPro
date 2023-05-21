#pragma once
#include <string>
class Teacher
{
private:
	std::string firstName;
	std::string lastName;
	std::string subject;
	int price;

public:
	Teacher(std::string lastName, std::string firstName, std::string subject, int price)
		: firstName(firstName),lastName(lastName),subject(subject), price(price) {}

	std::string getFirstName();
	std::string getLastName();
	std::string getSubject();
	int getPrice();

	~Teacher() {};
};