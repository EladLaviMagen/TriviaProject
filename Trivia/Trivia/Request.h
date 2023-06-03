#pragma once
#include <iostream>
#include <vector>
#include "IRequestHandler.h"

#define PASSWORD "password"
#define USERNAME "username"
#define EMAIL "mail"
#define ID_JSON "roomId"
#define TIME "time"
#define MAX_USERS "max"
#define QUESTION_COUNT "count"
#define NAME "name"

#define SIGN 3
#define LOGOUT 2
#define LOG 1
#define CREATEROOM 8
#define GETPLAYERSINROOM 7
#define JOINROOM 5
#define GETALLROOMS 9
#define GETPLAYERSTATS 6
#define GETHIGHSCORES 10
#define CLOSEROOM 11
#define STARTGAME 12
#define GETSTATE 13


class IRequestHandler;

typedef struct LoginRequest
{
	std::string username;
	std::string password;

} LoginRequest;

typedef struct SignUpRequest
{
	std::string username;
	std::string password;
	std::string email;
} SignUpRequest;


typedef struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
}RequestResult;



typedef struct RequestInfo
{
	unsigned char id;
	std::vector<unsigned char> buffer;
}RequestInfo;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

typedef struct JoinRoomRequest
{
	unsigned int roomId;
};



