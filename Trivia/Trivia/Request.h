#pragma once
#include <iostream>
#include <vector>
#include "LoginRequestHandler.h"
#include "Communicator.h"

#define PASSWORD "password"
#define USERNAME "username"
#define EMAIL "mail"
#define ID "roomId"

class LoginRequestHandler;
class Communicator;
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



