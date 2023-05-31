#pragma once
#include "Request.h"
#include <fstream>
#include "json.hpp"
#include <bitset>
#include "Helper.h"
using json = nlohmann::json;

struct LoginRequest;
struct SignUpRequest;
struct GetPlayersInRoomRequest;
struct JoinRoomRequest;
struct CreateRoomRequest;
class IRequestHandler;



class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignUpRequest deserializeSignupRequest(std::vector<unsigned char> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> buffer);
};

