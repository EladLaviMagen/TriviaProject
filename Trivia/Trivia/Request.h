#pragma once
#include <iostream>
#include <vector>
#include "IRequestHandler.h"
#include "Communicator.h"

struct LoginRequest
{
	std::string username;
	std::string password;
} typedef LoginRequest;

struct SignUpRequest
{
	std::string username;
	std::string password;
	std::string email;
}typedef SignUpRequest;


struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
}typedef RequestResult;



struct RequestInfo
{
	unsigned char id;
	std::vector<byte> buffer;
}typedef RequestInfo;



