#include "RoomMemberRequestHandler.h"
#define WAITING 0

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
    result.response = JsonResponsePacketSerializer::serializeEmptyResponse();
    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
    RequestResult result;
    RoomData data = m_room.getData();
    GetRoomStateResponse res;
    if(m_roomManager.getRoom(data.id).getData().isActive == WAITING)
    {
        res.answerTimeout = m_roomManager.getRoom(data.id).getData().timePerQuestion;
        res.hasGameBegun = false;
        res.players = m_roomManager.getRoom(data.id).getAllUsers();
        res.questionCount = m_roomManager.getRoom(data.id).getData().numOfQuestions;
        res.status = STATUS_SUCCESS;
        result.newHandler = this;
    }
    else if (m_roomManager.getRoom(data.id).getData().isActive == ROOMCLOSED)
    {
        result.newHandler = m_handlerFactory.createMenuRequestHandler(m_loggedUser);
        res.answerTimeout = 1;
        res.hasGameBegun = false;
        res.questionCount = 1;
        res.status = ROOMCLOSED;
        RequestResult grab = leaveRoom(info);
        delete grab.newHandler;
        grab.newHandler = nullptr;
        if (m_roomManager.getRoom(data.id).getAllUsers().size() == 0)
        {
            m_roomManager.deleteRoom(m_room.getData().id);
        }
    }
    else
    {
        result.newHandler = m_handlerFactory.createGameRequestHandler(m_loggedUser);
        res.answerTimeout = 1;
        res.hasGameBegun = true;
        res.questionCount = 1;
        res.status = GAMEBEGUN;
        RequestResult grab = leaveRoom(info);
        delete grab.newHandler;
        grab.newHandler = nullptr;
        if (m_roomManager.getRoom(data.id).getAllUsers().size() == 0)
        {
            m_roomManager.deleteRoom(m_room.getData().id);
        }
    }
    result.response = JsonResponsePacketSerializer::serializeResponse(res);
    return result;
}
