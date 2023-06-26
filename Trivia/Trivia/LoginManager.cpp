#include "LoginManager.h"
std::mutex LoginManager::login_lock;
//C'tor
LoginManager::LoginManager(IDatabase* database)
{
	std::lock_guard<std::mutex> locker(login_lock);
	m_database = database;
	m_loggedUsers = new std::vector<LoggedUser>();
}


void LoginManager::signUp(std::string name, std::string password, std::string mail)
{
	if (!m_database->doesUserExist(name))//if the user doesn't exist creating him and adding to logged users
	{
		std::lock_guard<std::mutex> locker(login_lock);
		m_database->addNewUser(name, password, mail);
		m_loggedUsers->push_back(LoggedUser(name));
	}
	else
	{
		throw UserNotExistException("okk what ever u say");
	}
	
}
void LoginManager::login(std::string name, std::string password)
{
	if (m_database->doesUserExist(name))//if the user exist
	{
		if (m_database->doesPasswordMatch(name, password))//checking if the password match if it is than adding to logged users
		{
			std::lock_guard<std::mutex> locker(login_lock);

			for (auto it = m_loggedUsers->begin(); it != m_loggedUsers->end(); it++)
			{
				if (it->getUserName() == name)//if the user already logged than return exs
				{
					throw(AccLoggedException("Account already logged in"));
				}
			}
			m_loggedUsers->push_back(LoggedUser(name));
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
	std::lock_guard<std::mutex> locker(login_lock);
	for (auto it = m_loggedUsers->begin(); it != m_loggedUsers->end(); it++)//checking out the user
	{
		if (it->getUserName() == name)
		{
			m_loggedUsers->erase(it);
			return;
		}
	}
}