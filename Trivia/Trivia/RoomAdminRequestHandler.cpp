#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser loggedUser, RoomManager* roomManager, RequestHandlerFactory* factory) : m_room(room), m_loggedUser(loggedUser), m_roomManager(roomManager), m_handlerFactory(factory)
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
    result.newHandler = m_handlerFactory->createMenuRequestHandler(this->m_loggedUser);
    m_roomManager->getRoom(m_room.getData().id).removeUser(m_loggedUser);
    CloseRoomResponse res;
    res.status = 1;
    result.response = JsonResponsePacketSerializer::serializeResponse(res);
    if (m_roomManager->getRoom(m_room.getData().id).getAllUsers().size() == 0)
    {
        m_roomManager->deleteRoom(m_room.getData().id);
    }
    else
    {
        m_roomManager->getRoom(m_room.getData().id).close();
    }
    return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
    RequestResult result;
    m_handlerFactory->getGameManager()->createGame(m_roomManager->getRoom(m_room.getData().id));
    result.newHandler = m_handlerFactory->createGameRequestHandler(this->m_loggedUser);
    m_roomManager->getRoom(m_room.getData().id).removeUser(m_loggedUser);
    StartGameResponse res;
    res.status = 1;
    result.response = JsonResponsePacketSerializer::serializeResponse(res);
    if (m_roomManager->getRoom(m_room.getData().id).getAllUsers().size() == 0)
    {
        m_roomManager->deleteRoom(m_room.getData().id);
    }
    else
    {
        m_roomManager->getRoom(m_room.getData().id).activate();
    }
    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
    RequestResult result;
    RoomData data = m_room.getData();
    GetRoomStateResponse res;
    res.answerTimeout = m_roomManager->getRoom(data.id).getData().timePerQuestion;
    res.hasGameBegun = false;
    res.players = m_roomManager->getRoom(data.id).getAllUsers();
    res.questionCount = m_roomManager->getRoom(data.id).getData().numOfQuestions;
    res.status = STATUS_SUCCESS;
    result.newHandler = this;
    result.response = JsonResponsePacketSerializer::serializeResponse(res);
    return result;
}
