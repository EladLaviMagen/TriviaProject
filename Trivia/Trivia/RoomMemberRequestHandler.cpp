#include "RoomMemberRequestHandler.h"
#define WAITING 0
//C'tor
RoomMemberRequestHandler::RoomMemberRequestHandler(Room room, LoggedUser loggedUser, RoomManager* roomManager, RequestHandlerFactory* factory) : m_room(room), m_loggedUser(loggedUser), m_roomManager(roomManager), m_handlerFactory(factory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
    if (info.id == LEAVEROOM || info.id == GETSTATE)//checking if the request is relevant
    {
        return true;
    }
    return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
    //giving the right handling for the request
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
    //sending to the client a leaving room resposnse
    RequestResult result;
    result.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_loggedUser);//changing to menu handler
    this->m_roomManager->getRoom(m_room.getData().id).removeUser(m_loggedUser);
    LeaveRoomResponse res;
    res.status = 1;
    result.response = JsonResponsePacketSerializer::serializeResponse(res);
    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{ 
    RequestResult result;
    RoomData data = m_room.getData();
    GetRoomStateResponse res;
    res.answerTimeout = m_roomManager->getRoom(data.id).getData().timePerQuestion;
    res.hasGameBegun = false;
    res.players = m_roomManager->getRoom(data.id).getAllUsers();
    res.questionCount = m_roomManager->getRoom(data.id).getData().numOfQuestions;//getting room info
    if(m_roomManager->getRoom(data.id).getData().isActive == WAITING)//if room is still waiting nothing happens
    {
        res.status = STATUS_SUCCESS;
        result.newHandler = this;
    }
    else if (m_roomManager->getRoom(data.id).getData().isActive == ROOMCLOSED)//if room is closed return the user to the menu
    {
        result.newHandler = m_handlerFactory->createMenuRequestHandler(m_loggedUser);
        res.status = ROOMCLOSED;
        RequestResult grab = leaveRoom(info);
        delete grab.newHandler;
        grab.newHandler = nullptr;
        if (m_roomManager->getRoom(data.id).getAllUsers().size() == 0)//deleting room if there no users
        {
            m_roomManager->deleteRoom(m_room.getData().id);
        }
    }
    else//if game started
    {
        result.newHandler = m_handlerFactory->createGameRequestHandler(m_loggedUser);
        res.status = GAMEBEGUN;
        RequestResult grab = leaveRoom(info);//leaving room
        delete grab.newHandler;
        grab.newHandler = nullptr;
        if (m_roomManager->getRoom(data.id).getAllUsers().size() == 0)//delete room if empty
        {
            m_roomManager->deleteRoom(m_room.getData().id);
        }
    }
    result.response = JsonResponsePacketSerializer::serializeResponse(res);
    return result;
}
