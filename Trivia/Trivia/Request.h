#include <iostream>

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