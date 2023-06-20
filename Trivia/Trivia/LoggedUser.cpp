#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string name)
{
	m_username = name;
}

std::string LoggedUser::getUserName()
{
	return this->m_username;
}

void LoggedUser::signout()
{
	m_username = "";
}
