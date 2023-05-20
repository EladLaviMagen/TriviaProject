#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "SqliteDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(LoginManager m_login, IDatabase* m_data);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
};

