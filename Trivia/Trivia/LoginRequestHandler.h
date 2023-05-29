#pragma once
#include "IRequestHandler.h"

class RequestHandlerFactory;
class IRequestHandler;
class LoginManager;
struct RequestInfo;
struct RequestResult;


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
