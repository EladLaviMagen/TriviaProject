#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory), m_user(user)
{}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.id == RELEVANT)
	{
		return true;
	}
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::signout(RequestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(RequestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(RequestInfo)
{
	return RequestResult();
}
