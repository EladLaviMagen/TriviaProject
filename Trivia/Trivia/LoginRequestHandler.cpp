#include "LoginRequestHandler.h"
//C'tor
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager) : m_handlerFactory(handlerFactory), m_loginManager(loginManager)
{}
bool LoginRequestHandler::isRequestRelevant(RequestInfo info)//checking if relevant
{
    if (info.id == SIGN || info.id == LOG)
    {
        return true;
    }
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    //giving the right handling for the request
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
    LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);//getting login msg
    LoginResponse response = { STATUS_SUCCESS };
    try
    {
        m_loginManager.login(request.username, request.password);//log him in and sending a proper response
        result.response = JsonResponsePacketSerializer::serializeResponse(response);
        result.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(request.username));//sending the boy to the menu

    }
    catch (MyException& ex)//if there was an error 
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
    SignUpRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);//getting sign up msg
    SignUpResponse response = { STATUS_SUCCESS };
    try
    {
        m_loginManager.signUp(request.username, request.password, request.email);//sign this shit up and sending a proper response
        result.response = JsonResponsePacketSerializer::serializeResponse(response);
        result.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(request.username));//sending the boy to the menu
    }
    catch (MyException& ex)//if there was an error 
    {
        ErrorResponse err = { ex.what() };
        result.response = JsonResponsePacketSerializer::serializeResponse(err);
        result.newHandler = this;
    }
    return result;
}
