#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
    return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
    return RequestResult();
}
