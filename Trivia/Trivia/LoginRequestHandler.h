#pragma once
#include "IRequestHandler.h"
#include "Request.h"
#include "Request.h"
#include "JsonRequestPacketDeserializer.h"

#define SIGN 7
#define LOG 3
#define STATUS_SUCCESS 1
#define STATUS_FAILED 0

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
};
