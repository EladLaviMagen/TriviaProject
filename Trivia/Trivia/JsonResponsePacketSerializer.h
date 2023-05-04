#pragma once
#include "Response.h"
#include <vector>
#include <fstream>
#include "json.hpp"
#include "Helper.h"
class JsonResponsePacketSerializer
{
	static std::vector<unsigned char> serializeResponse(ErrorResponse err);
	static std::vector<unsigned char> serializeResponse(LoginResponse log);
	static std::vector<unsigned char> serializeResponse(SignUpResponse sign);
};

