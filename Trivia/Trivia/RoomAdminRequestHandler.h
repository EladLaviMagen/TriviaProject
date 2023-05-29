#pragma once
#include "Room.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RoomManager;
class RequestHandlerFactory;
class Room;

class RoomAdminRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);


private:
	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);

	Room m_room;
	LoggedUser m_loggedUser;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};

