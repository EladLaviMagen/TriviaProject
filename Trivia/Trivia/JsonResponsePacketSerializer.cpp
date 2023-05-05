#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	json buff;
	buff[MESSAGE] = err.message;
	std::string bufferStr = "";
	bufferStr += ERROR_CODE;
	std::string ser = buff.dump();
	int size = ser.length();
	std::string buffSize = Helper::getPaddedNumber(size, 5);
	bufferStr += buffSize + ser;
	std::vector<unsigned char> output;
	for (int i = 0; i < bufferStr.size(); ++i) 
	{
		output.push_back(static_cast<unsigned char>(std::bitset<8>(bufferStr[i]).to_ulong())); //create the bitset for the inputed c string
	}
	return output;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	json buff;
	buff[STATUS] = log.status;
	std::string bufferStr = "";
	bufferStr += ERROR_CODE;
	std::string ser = buff.dump();
	int size = ser.length();
	std::string buffSize = Helper::getPaddedNumber(size, 5);
	bufferStr += buffSize + ser;
	std::vector<unsigned char> output;
	for (int i = 0; i < bufferStr.size(); ++i)
	{
		output.push_back(static_cast<unsigned char>(std::bitset<8>(bufferStr[i]).to_ulong())); //create the bitset for the inputed c string
	}
	return output;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignUpResponse sign)
{
	json buff;
	buff[STATUS] = sign.status;
	std::string bufferStr = "";
	bufferStr += ERROR_CODE;
	std::string ser = buff.dump();
	int size = ser.length();
	std::string buffSize = Helper::getPaddedNumber(size, 5);
	bufferStr += buffSize + ser;
	std::vector<unsigned char> output;
	for (int i = 0; i < bufferStr.size(); ++i)
	{
		output.push_back(static_cast<unsigned char>(std::bitset<8>(bufferStr[i]).to_ulong())); //create the bitset for the inputed c string
	}
	return output;
}
