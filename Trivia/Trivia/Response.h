#include <iostream>
#define STATUS "status"
#define MESSAGE "message"
#define SUCCESS_CODE '1'
#define FAILURE_CODE '4'
#define ERROR_CODE '0'
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