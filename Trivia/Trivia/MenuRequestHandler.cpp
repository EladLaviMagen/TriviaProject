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

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	RequestResult result;
	m_handlerFactory.getLoginManager().logout(m_user.getUserName());
	for (int i = 1; i < m_roomManager.getID(); i++)
	{
		m_roomManager.getRoom(i).removeUser(m_user);
	}
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
	std::vector<RoomData> rooms = m_roomManager.getRooms();
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
	response.players = this->m_roomManager.getRoom(data.roomId).getAllUsers();
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	RequestResult result;
	JoinRoomRequest req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	JoinRoomResponse response;
	if (m_roomManager.getRoomState(req.roomId) == 1)
	{
		response.status = STATUS_FAILED;
		result.newHandler = this;
	}
	else
	{
		response.status = STATUS_SUCCESS;
		result.newHandler = nullptr;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	RequestResult result;
	CreateRoomRequest details = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
	RoomData room;
	room.id = m_roomManager.assignID();
	room.isActive = 0;
	this->m_roomManager.createRoom(this->m_user, room);
	CreateRoomResponse response;
	response.status = STATUS_SUCCESS;
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
