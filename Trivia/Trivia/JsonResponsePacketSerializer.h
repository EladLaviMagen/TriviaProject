#pragma once
#include "Response.h"
#include <vector>
#include <fstream>
#include "json.hpp"
#include "Helper.h"
#include <bitset>

struct ErrorResponse;
struct LoginResponse;
struct SignUpResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse err);
	static std::vector<unsigned char> serializeResponse(LoginResponse log);
	static std::vector<unsigned char> serializeResponse(SignUpResponse sign);
};

