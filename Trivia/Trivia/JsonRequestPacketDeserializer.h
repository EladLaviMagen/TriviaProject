#pragma once
#include "Request.h"
#include <fstream>
#include "json.hpp"

struct LoginRequest;
struct SignUpRequest;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignUpRequest deserializeSignupRequest(std::vector<unsigned char> buffer);
};

