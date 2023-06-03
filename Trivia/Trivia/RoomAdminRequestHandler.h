#pragma once
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "RoomNotExist.h"

class RequestHandlerFactory;




class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(Room room, LoggedUser loggedUser, RoomManager roomManager, RequestHandlerFactory factory);
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;


private:
	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);

	Room m_room;
	LoggedUser m_loggedUser;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};

