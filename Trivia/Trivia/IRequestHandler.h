#pragma once
#include "Request.h"
#include "Response.h"
#include "JsonRequestPacketDeserializer.h"


#define STATUS_SUCCESS 1
#define STATUS_FAILED 0

class JsonRequestPacketDeserializer;
struct LoginRequest;
struct SignUpRequest;
struct CreateRoomRequest;
struct GetPlayersInRoomRequest;
struct JoinRoomRequest;
struct LoginResponse;
struct SignUpResponse;
struct ErrorResponse;
struct LogoutResponse;
struct GetRoomsResponse;
struct GetPlayersInRoomResponse;
struct getHighScoreResponse;
struct getPersonalStatsResponse;
struct JoinRoomResponse;
struct CreateRoomResponse;
struct GetRoomStateResponse;
struct LeaveRoomResponse;
struct StartGameResponse;
struct CloseRoomResponse;
struct RequestInfo;
struct RequestResult;


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};
