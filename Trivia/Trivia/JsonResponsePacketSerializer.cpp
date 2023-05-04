#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	json buff;
	buff[MESSAGE] = err.message;
	std::string ser = buff.dump();
	std::vector<unsigned char> ret;
	for (int i = 0; i < ser.length(); i++)
	{
		ret.push_back(ser[i]);
	}
	return ret;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	json buff;
	buff[STATUS] = log.status;
	std::string ser = buff.dump();
	std::vector<unsigned char> ret;
	for (int i = 0; i < ser.length(); i++)
	{
		ret.push_back(ser[i]);
	}
	return ret;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignUpResponse sign)
{
	json buff;
	buff[STATUS] = sign.status;
	std::string ser = buff.dump();
	std::vector<unsigned char> ret;
	for (int i = 0; i < ser.length(); i++)
	{
		ret.push_back(ser[i]);
	}
	return ret;
}
