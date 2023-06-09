#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser loggedUser, RoomManager roomManager, RequestHandlerFactory factory) : m_room(room), m_loggedUser(loggedUser), m_roomManager(roomManager), m_handlerFactory(factory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
    if (info.id == CLOSEROOM || info.id == STARTGAME || info.id == GETSTATE)
    {
        return true;
    }
    return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    if (info.id == CLOSEROOM)
    {
        result = closeRoom(info);
    }
    else if (info.id == STARTGAME)
    {
        result = startGame(info);
    }
    else
    {
        result = getRoomState(info);
    }
    return result;
    
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
    RequestResult result;
    result.newHandler = m_handlerFactory.createMenuRequestHandler(this->m_loggedUser);
    m_roomManager.deleteRoom(m_room.getData().id);
    return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
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
        res.status = STATUS_SUCCESS;
    }
    result.response = JsonResponsePacketSerializer::serializeResponse(res);
    return result;
}
