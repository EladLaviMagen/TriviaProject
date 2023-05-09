#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{}
bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    if (info.id == SIGN || info.id == LOG)
    {
        return true;
    }
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    if (info.id == SIGN)
    {
        SignUpRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
        std::cout << request.username << "\n" << request.username << "\n" << request.email << "\n";
        SignUpResponse response = { STATUS_SUCCESS };
        result.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    else
    {
        LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
        std::cout << request.username << "\n" << request.username << "\n";
        LoginResponse response = { STATUS_SUCCESS };
        result.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    //for now, no other handlers yet
    result.newHandler = nullptr;
    return result;
}
