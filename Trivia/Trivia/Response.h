#include <iostream>
#define STATUS "status"
#define MESSAGE "message"
struct LoginResponse
{
	unsigned int status;
}typedef LoginResponse;

struct SignUpResponse
{
	unsigned int status;
}typedef SignUpResponse;

struct ErrorResponse
{
	std::string message;
}typedef ErrorResponse;