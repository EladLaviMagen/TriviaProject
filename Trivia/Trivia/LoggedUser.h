#pragma once
#include <iostream>
class LoggedUser
{
public:
	LoggedUser();
	std::string getUserName();
private:
	std::string m_username;
};

