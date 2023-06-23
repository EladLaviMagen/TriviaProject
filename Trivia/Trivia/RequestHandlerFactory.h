#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"
#include "SqliteDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "GameManager.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class GameRequestHandler;
class StatisticsManager;
class LoginManager;
class RoomManager;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(LoginManager m_login, IDatabase* m_data, StatisticsManager m_statistics);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	StatisticsManager& getStatisticsManager();
	RoomManager* getRoomManager();
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser loggedUser, Room room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser loggedUser, Room room);
	GameRequestHandler* createGameRequestHandler(LoggedUser);
	GameManager* getGameManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager* m_roomManager;
	StatisticsManager m_StatisticsManager;
	GameManager* m_gameManager;
};

