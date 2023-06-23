#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager* roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory), m_user(user)
{}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.id == LOGOUT || info.id == JOINROOM || info.id == GETPLAYERSTATS || info.id == GETPLAYERSINROOM || info.id == CREATEROOM || info.id == GETALLROOMS || info.id == GETHIGHSCORES)
	{
		return true;
	}
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult result;
	if (info.id == LOGOUT)
	{
		result = signout(info);
	}
	else if(info.id == JOINROOM)
	{
		result = joinRoom(info);
	}
	else if (info.id == GETPLAYERSTATS)
	{
		result = getPersonalStats(info);
	}
	else if (info.id == GETPLAYERSINROOM)
	{
		result = getPlayersInRoom(info);
	}
	else if (info.id == CREATEROOM)
	{
		result = createRoom(info);
	}
	else if (info.id == GETALLROOMS)
	{
		result = getRooms(info);
	}
	else
	{
		result = getHighScore(info);
	}
	return result;
}

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	RequestResult result;
	m_handlerFactory.getLoginManager().logout(m_user.getUserName());
	LogoutResponse response;
	response.status = STATUS_SUCCESS;
	result.newHandler = m_handlerFactory.createLoginRequestHandler();
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	RequestResult result;
	GetRoomsResponse response;
	std::vector<RoomData> rooms = m_roomManager->getRooms();
	response.rooms = rooms;
	response.status = STATUS_SUCCESS;
	result.newHandler = this;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	RequestResult result;
	GetPlayersInRoomResponse response;
	GetPlayersInRoomRequest data = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer);
	response.players = this->m_roomManager->getRoom(data.roomId).getAllUsers();
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
	RequestResult result;
	getPersonalStatsResponse response;
	response.status = STATUS_SUCCESS;
	response.statistics = m_statisticsManager.getUserStatistics(m_user.getUserName());
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this;
	return result;

}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
	RequestResult result;
	getPersonalStatsResponse response;
	response.status = STATUS_SUCCESS;
	response.statistics = m_statisticsManager.getHighScore();
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	RequestResult result;
	JoinRoomRequest req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	JoinRoomResponse response;
	if (m_roomManager->getRoomState(req.roomId) == 0 && m_roomManager->getRoom(req.roomId).getAllUsers().size() < m_roomManager->getRoom(req.roomId).getData().maxPlayers)
	{
		response.status = STATUS_SUCCESS;
		result.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user, m_roomManager->getRoom(req.roomId));
		m_roomManager->getRoom(req.roomId).addUser(m_user);
		
	}
	else
	{
		response.status = STATUS_FAILED;
		result.newHandler = this;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	RequestResult result;
	CreateRoomRequest details = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
	RoomData room;
	room.id = m_roomManager->getID();
	room.isActive = 0;
	room.maxPlayers = details.maxUsers;
	room.name = details.roomName;
	room.numOfQuestions = details.questionCount;
	room.timePerQuestion = details.answerTimeout;
	this->m_roomManager->createRoom(this->m_user, room);
	CreateRoomResponse response;
	response.status = STATUS_SUCCESS;
	result.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_roomManager->getRoom(room.id));
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
