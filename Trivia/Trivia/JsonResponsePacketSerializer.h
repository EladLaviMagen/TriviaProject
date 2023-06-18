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
struct LogoutResponse;
struct GetRoomsResponse;
struct GetPlayersInRoomResponse;
struct JoinRoomResponse;
struct CreateRoomResponse;
struct getHighScoreResponse;
struct getPersonalStatsResponse;
struct CloseRoomResponse;
struct StartGameResponse;
struct GetRoomStateResponse;
struct LeaveRoomResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse err);
	static std::vector<unsigned char> serializeResponse(LoginResponse log);
	static std::vector<unsigned char> serializeResponse(SignUpResponse sign);
	static std::vector<unsigned char> serializeResponse(LogoutResponse res);
	static std::vector<unsigned char> serializeResponse(GetRoomsResponse res);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse res);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse res);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse res);
	static std::vector<unsigned char> serializeResponse(getHighScoreResponse res);
	static std::vector<unsigned char> serializeResponse(getPersonalStatsResponse res);
	static std::vector<unsigned char> serializeResponse(CloseRoomResponse close);
	static std::vector<unsigned char> serializeResponse(StartGameResponse start);
	static std::vector<unsigned char> serializeResponse(GetRoomStateResponse state);
	static std::vector<unsigned char> serializeResponse(LeaveRoomResponse leave);
	static std::vector<unsigned char> serializeResponse(GetGameResultsResponse gameRes);
	static std::vector<unsigned char> serializeResponse(SubmitAnswerResponse res);
	static std::vector<unsigned char> serializeResponse(GetQuestionResponse res);
	static std::vector<unsigned char> serializeResponse(LeaveGameResponse res);
	static std::vector<unsigned char> serializeEmptyResponse();
};

