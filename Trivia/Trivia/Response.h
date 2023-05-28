#pragma once
#include <iostream>
#include "LoginRequestHandler.h"
#include "Communicator.h"
#include "Room.h"
#define STATUS "status"
#define MESSAGE "message"
#define PLAYERS "players"
#define STATISTICS "stats"
#define ROOMS "rooms"
#define QCOUNT "questionCount"
#define ANSTIMEOUT "answerTimeout"
#define HASBEG "has game begun"
#define SUCCESS_CODE "00000001"
#define FAILURE_CODE "00000100"
#define ERROR_CODE "00000000"

class LoginRequestHandler;
class Communicator;
class IRequestHandler;

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct SignUpResponse
{
	unsigned int status;
} SignUpResponse;

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

typedef struct LogoutResponse
{
	unsigned int status;
};

typedef struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

typedef struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
};

typedef struct getHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};

typedef struct getPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};

typedef struct JoinRoomResponse
{
	unsigned int status;
};

typedef struct CreateRoomResponse
{
	unsigned int status;
};

typedef struct CloseRoomResponse
{
	unsigned int status;
};

typedef struct StartGameResponse
{
	unsigned int status;
};

typedef struct LeaveRoomResponse
{
	unsigned int status;
};

typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};
