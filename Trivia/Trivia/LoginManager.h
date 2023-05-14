#pragma once
#include <iostream>
#include <string>
#include "SqliteDatabase.h"
#include <vector>
#include "LoggedUser.h"
#include "UserNotExistException.h"
#include "AccLoggedException.h"
#include "IncorrectPasswordException.h"

class LoginManager
{
public:
	LoginManager(IDatabase* database);
	void signUp(std::string name, std::string password, std::string mail);
	void login(std::string name, std::string password);
	void logout(std::string name);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};

