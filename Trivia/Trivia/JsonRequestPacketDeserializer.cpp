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
	int size = 0;
	std::string biSize = "";

	for (int i = 0; i < SIZE / 8; i++)
	{
		biSize = "";
		size *= 10;
		for (size_t i = 0; i < CODE; i++)
		{
			biSize += buffer[0];
			buffer.erase(buffer.begin());
		}
		size += std::stoi(biSize, 0, 2);
	}
	std::string str = "";
	for (int i = 0; i < size * 8; i++)
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
	int size = 0;
	std::string biSize = "";

	for (int i = 0; i < SIZE / 8; i++)
	{
		biSize = "";
		size *= 10;
		for (size_t i = 0; i < CODE; i++)
		{
			biSize += buffer[0];
			buffer.erase(buffer.begin());
		}
		size += std::stoi(biSize, 0, 2);
	}
	std::string str = "";
	for (int i = 0; i < size * 8; i++)
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
