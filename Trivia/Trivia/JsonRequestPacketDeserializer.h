#pragma once
#include "Request.h"
#include <fstream>
#include "json.hpp"
class JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignUpRequest deserializeSignupRequest(std::vector<unsigned char> buffer);
};

