#include "LoginManager.h"


LoginManager::LoginManager(IDatabase* database)
{
	m_database = database;
	m_loggedUsers.push_back(LoggedUser("Dummy"));
}

void LoginManager::signUp(std::string name, std::string password, std::string mail)
{
	if (!m_database->doesUserExist(name))
	{
		m_database->addNewUser(name, password, mail);
		m_loggedUsers.push_back(LoggedUser(name));
	}
	else
	{
		throw UserNotExistException("User does not exists");
	}
	
}
void LoginManager::login(std::string name, std::string password)
{
	if (m_database->doesUserExist(name))
	{
		if (m_database->doesPasswordMatch(name, password))
		{
			for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
			{
				if (it->getUserName() == name)
				{
					throw(AccLoggedException("Account already logged in"));
				}
			}
			m_loggedUsers.push_back(LoggedUser(name));
		}
		else
		{
			throw IncorrectPasswordException("Incorrect password");
		}
		
	}
	else
	{
		throw UserNotExistException("User doesn't exist");
	}
}
void LoginManager::logout(std::string name)
{
	bool notDeleted = true;
	for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
	{
		if (it->getUserName() == name)
		{
			m_loggedUsers.erase(it);
			notDeleted = false;
		}
	}
}