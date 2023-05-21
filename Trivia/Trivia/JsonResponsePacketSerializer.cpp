#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;

std::string int_to_bin_str(int num) {
	std::string binary = "";

	while (num > 0) {
		int digit = num % 2;
		binary = std::to_string(digit) + binary;
		num = num / 2;
	}

	return binary;
}

std::vector<std::string> roomToString(std::vector<RoomData> vec)
{
	std::vector<std::string> rooms;
	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		rooms.push_back(std::to_string(it->id));
		rooms.push_back(std::to_string(it->isActive));
		rooms.push_back(std::to_string(it->maxPlayers));
		rooms.push_back(it->name);
		rooms.push_back(std::to_string(it->numOfQuestions));
		rooms.push_back(std::to_string(it->timePerQuestion));
	}
	return rooms;
}

std::string str_to_bin_str(const std::string& str) {
	std::string binary_str = "";
	for (char c : str) {
		// Convert the character to its ASCII code and then to binary string
		binary_str += std::bitset<8>(c).to_string();
	}
	return binary_str;
}

std::vector<unsigned char> createBuffer(json buff, std::string code)
{
	std::string bufferStr = "";
	bufferStr += code;
	std::string ser = buff.dump();
	int size = ser.length();
	std::string buffSize = int_to_bin_str(size);
	for (int i = buffSize.length(); i < 32; i++)
	{
		buffSize = '0' + buffSize;
	}
	bufferStr += buffSize + str_to_bin_str(ser);
	std::vector<unsigned char> output;
	for (int i = 0; i < bufferStr.length(); i++)
	{
		output.push_back(bufferStr[i]);
	}
	return output;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	json buff;
	buff[MESSAGE] = err.message;
	return createBuffer(buff, ERROR_CODE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	json buff;
	buff[STATUS] = log.status;
	return createBuffer(buff, SUCCESS_CODE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignUpResponse sign)
{
	json buff;
	buff[STATUS] = sign.status;
	return createBuffer(buff, SUCCESS_CODE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse res)
{
	
	json buff;
	buff[STATUS] = res.status;
	return createBuffer(buff, SUCCESS_CODE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse res)
{
	json buff;
	buff[STATUS] = res.status;
	buff[ROOMS] = roomToString(res.rooms);
	return createBuffer(buff, SUCCESS_CODE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerResponse(GetPlayersInRoomResponse res)
{
	json buff;
	buff[PLAYERS] = res.players;
	return createBuffer(buff, SUCCESS_CODE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse res)
{
	json buff;
	buff[STATUS] = res.status;
	return createBuffer(buff, SUCCESS_CODE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse res)
{
	json buff;
	buff[STATUS] = res.status;
	return createBuffer(buff, SUCCESS_CODE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse res)
{
	json buff;
	buff[STATUS] = res.status;
	buff[STATISTICS] = res.statistics;
	return createBuffer(buff, SUCCESS_CODE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse res)
{
	json buff;
	buff[STATUS] = res.status;
	buff[STATISTICS] = res.statistics;
	return createBuffer(buff, SUCCESS_CODE);
}
