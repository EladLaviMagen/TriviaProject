#pragma once
#include "Request.h"
#include "Response.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"

#define STATUS_SUCCESS 1
#define STATUS_FAILED 0

struct RequestInfo;
struct RequestResult;
class LoggedUser;
class RoomManager;
class StatisticsManager;
class RequestHandlerFactory;
struct RequestInfo;
struct RequestResult;
class JsonRequestPacketDeserializer;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};
