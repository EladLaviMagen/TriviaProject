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
        result = signUp(info);
    }
    else
    {
        result = login(info);
    }
    return result;
}

RequestResult LoginRequestHandler::login(RequestInfo info)
{
    RequestResult result;
    LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
    LoginResponse response = { STATUS_SUCCESS };
    try
    {
        m_loginManager.login(request.username, request.password);
        result.response = JsonResponsePacketSerializer::serializeResponse(response);

    }
    catch (MyException& ex)
    {
        ErrorResponse err = { ex.what() };
        result.response = JsonResponsePacketSerializer::serializeResponse(err);
        result.newHandler = this;
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
        result.newHandler = this;
    }
    return result;
}
