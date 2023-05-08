#pragma once
#include "Request.h"
#include "Response.h"

struct RequestInfo;
struct RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};
