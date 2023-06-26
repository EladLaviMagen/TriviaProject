#pragma once
#include "RequestHandlerFactory.h"


class RequestHandlerFactory;
class RoomManager;
class StatisticsManager;
class LoginManager;
struct RequestInfo;
struct RequestResult;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RoomManager* roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory* handlerFactory);
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;

	
private:
	RequestResult signout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult getPersonalStats(RequestInfo info);
	RequestResult getHighScore(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);

	LoggedUser m_user;
	RoomManager* m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory* m_handlerFactory;
};

