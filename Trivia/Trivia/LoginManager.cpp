#include "LoginManager.h"
std::mutex LoginManager::login_lock;

LoginManager::LoginManager(IDatabase* database)
{
	std::lock_guard<std::mutex> locker(login_lock);
	m_database = database;
}

void LoginManager::signUp(std::string name, std::string password, std::string mail)
{
	if (!m_database->doesUserExist(name))
	{
		std::lock_guard<std::mutex> locker(login_lock);
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
			std::lock_guard<std::mutex> locker(login_lock);
			for (int i = 0; i < m_loggedUsers.size(); i++)
			{
				if (m_loggedUsers[i].getUserName() == name)
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
	for (int i = 0; i < m_loggedUsers.size(); i++)
	{
		if (m_loggedUsers[i].getUserName() == name)
		{
			m_loggedUsers[i].signout();
		}
	}
}