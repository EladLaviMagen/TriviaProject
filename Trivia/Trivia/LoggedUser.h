#pragma once
#include <iostream>
class LoggedUser
{
public:
	LoggedUser(std::string name);
	std::string getUserName();
	void signout();
	bool operator==(LoggedUser other);
private:
	std::string m_username;
};

