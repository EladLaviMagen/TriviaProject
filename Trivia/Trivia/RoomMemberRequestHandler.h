#pragma once
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "RoomNotExist.h"

#define ROOMCLOSED


class RequestHandlerFactory;



class RoomMemberRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
private:
	RequestResult leaveRoom(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);

	Room m_room;
	LoggedUser m_loggedUser;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};

