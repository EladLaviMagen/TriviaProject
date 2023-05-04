#include "JsonRequestPacketDeserializer.h"

using json = nlohmann::json;

#include <bitset>


std::string binaryToString(std::string binaryStr) {
	std::string str = "";
	for (int i = 0; i < binaryStr.length(); i += 8) {
		std::string byteStr = binaryStr.substr(i, 8);
		std::bitset<8> byte(byteStr);
		str += static_cast<char>(byte.to_ulong());
	}
	return str;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	int size = int(buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3]);
	for (int i = 0; i < 4; i++)
	{
		buffer.erase(buffer.begin());
	}
	std::string str = "";
	for (int i = 0; i < size; i++)
	{
		str += buffer[i];
	}
	str = binaryToString(str);
	json j = json::parse(str);

	LoginRequest log;
	log.password = j[PASSWORD];
	log.username = j[USERNAME];
	return log;
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	int size = int(buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3]);
	for (int i = 0; i < 4; i++)
	{
		buffer.erase(buffer.begin());
	}
	std::string str = "";
	for (int i = 0; i < size; i++)
	{
		str += buffer[i];
	}
	str = binaryToString(str);
	json j = json::parse(str);

	SignUpRequest sign;
	sign.password = j[PASSWORD];
	sign.username = j[USERNAME];
	sign.email = j[EMAIL];
	return sign;
}
