#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room room, LoggedUser loggedUser, RoomManager roomManager, RequestHandlerFactory factory) : m_room(room), m_loggedUser(loggedUser), m_roomManager(roomManager), m_handlerFactory(factory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
    if (info.id == LEAVEROOM || info.id == GETSTATE)
    {
        return true;
    }
    return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    if (info.id == LEAVEROOM)
    {
        result = leaveRoom(info);
    }
    else
    {
        result = getRoomState(info);
    }
    return result;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
    RequestResult result;
    this->m_room.removeUser(m_loggedUser);
    result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser);
    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
    RequestResult result;
    RoomData data = m_room.getData();
    GetRoomStateResponse res;
    try
    {
        res.answerTimeout = m_roomManager.getRoom(data.id).getData().timePerQuestion;
        res.hasGameBegun = m_roomManager.getRoom(data.id).getData().isActive;
        res.players = m_roomManager.getRoom(data.id).getAllUsers();
        res.questionCount = m_roomManager.getRoom(data.id).getData().numOfQuestions;
        res.status = STATUS_SUCCESS;
        result.newHandler = this;
    }
    catch (RoomNotExist& ex)
    {
        result.newHandler = m_handlerFactory.createMenuRequestHandler(m_loggedUser);
        res.answerTimeout = 1;
        res.hasGameBegun = 3;
        res.questionCount = 1;
        res.status = ROOMCLOSED;
    }
    result.response = JsonResponsePacketSerializer::serializeResponse(res);
    return result;
}
