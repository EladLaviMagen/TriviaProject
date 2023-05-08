#pragma once
#include <iostream>
#include "LoginRequestHandler.h"
#include "Communicator.h"
#define STATUS "status"
#define MESSAGE "message"
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