#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager) : m_handlerFactory(handlerFactory), m_loginManager(loginManager)
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
        
        
        

       
        
    }
    else
    {
        
    }
    //for now, no other handlers yet
    result.newHandler = nullptr;
    return result;
}

RequestResult LoginRequestHandler::login(RequestInfo info)
{
    RequestResult result;
    SignUpRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
    SignUpResponse response = { STATUS_SUCCESS };
    try
    {
        m_loginManager.signUp(request.username, request.password, request.email);
        result.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    catch (MyException& ex)
    {
        ErrorResponse err = { ex.what() };
        result.response = JsonResponsePacketSerializer::serializeResponse(err);
    }
    return result;
}

RequestResult LoginRequestHandler::signUp(RequestInfo info)
{
    RequestResult result;
    SignUpRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    SignUpResponse response = { STATUS_SUCCESS };
    try
    {
        m_loginManager.signUp(request.username, request.password, request.email);
        result.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    catch (MyException& ex)
    {
        ErrorResponse err = { ex.what() };
        result.response = JsonResponsePacketSerializer::serializeResponse(err);
    }
    return result;
}
