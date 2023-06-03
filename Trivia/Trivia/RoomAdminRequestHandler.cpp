#include "RoomAdminRequestHandler.h"

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
    res.answerTimeout = data.timePerQuestion;
    res.hasGameBegun = data.isActive;
    res.players = m_room.getAllUsers();
    res.questionCount = data.numOfQuestions;
    res.status = STATUS_SUCCESS;
    result.newHandler = this;
    result.response = JsonResponsePacketSerializer::serializeResponse(res);
}
