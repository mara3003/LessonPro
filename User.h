#pragma once
#include <string>

class User
{
	private:
	const std::string username;
	const std::string password;
	const std::string email;
	const std::string lastName;
	const std::string firstName;
	const std::string schoolName;
	int grade;
	
	int id;
public:
	User() {}
	User(const std::string& username, const std::string& password, const std::string& lastName, const std::string& firstName,  const std::string& email,const std::string& school,const int& grade )
		:  username(username), email(email),firstName(firstName),lastName(lastName),password(password),schoolName(school),grade(grade) {}
	~User() {};

	const std::string getUsername();
	const std::string getPassword();
	const std::string getEmail();
	const std::string getlastName();
	const std::string getfirstName();
	const std::string getschoolName();
	const int getGrade();
};

