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
    return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
    return RequestResult();
}
