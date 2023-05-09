#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"

class IRequestHandler;
#define SIGN 3
#define LOG 1
#define STATUS_SUCCESS 1
#define STATUS_FAILED 0

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
};
