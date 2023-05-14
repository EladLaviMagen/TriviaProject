#pragma once
#include <iostream>
class LoggedUser
{
public:
	LoggedUser(std::string name);
	std::string getUserName();
private:
	std::string m_username;
};

