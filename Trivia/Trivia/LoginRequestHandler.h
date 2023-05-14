#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"
class RequestHandlerFactory;
class IRequestHandler;
#define SIGN 3
#define LOG 1
#define STATUS_SUCCESS 1
#define STATUS_FAILED 0

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager);
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
private:
	RequestResult login(RequestInfo);
	RequestResult signUp(RequestInfo);
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;
};
