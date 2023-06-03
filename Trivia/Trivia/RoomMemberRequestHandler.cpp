#include "RoomMemberRequestHandler.h"

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
    return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
    return RequestResult();
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
        result.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    catch ()
    {

    }
}
