#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
struct RequestInfo;
struct RequestResult;
class RoomManager;
class StatisticsManager;
class LoginManager;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager);
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
private:
	RequestResult login(RequestInfo info);
	RequestResult signUp(RequestInfo info);
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;
};