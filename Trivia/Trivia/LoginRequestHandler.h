#pragma once
#include "IRequestHandler.h"
#include "Request.h"
class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
};
