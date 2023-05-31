#pragma once
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"


class RequestHandlerFactory;




class RoomAdminRequestHandler : public IRequestHandler
{
public:
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

