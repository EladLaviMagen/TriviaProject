#include "JsonRequestPacketDeserializer.h"





std::string binaryToString(std::string binaryStr) {
	std::string str = "";
	for (int i = 0; i < binaryStr.length(); i += 8) {
		std::string byteStr = binaryStr.substr(i, 8);
		std::bitset<8> byte(byteStr);
		str += static_cast<char>(byte.to_ulong());
	}
	return str;
}

json createJson(std::vector<unsigned char> buffer)
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
	return j;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	
	json j = createJson(buffer);

	LoginRequest log;
	log.password = j[PASSWORD];
	log.username = j[USERNAME];
	return log;
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	json j = createJson(buffer);
	SignUpRequest sign;
	sign.password = j[PASSWORD];
	sign.username = j[USERNAME];
	sign.email = j[EMAIL];
	return sign;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> buffer)
{
	json j = createJson(buffer);
	GetPlayersInRoomRequest getP;
	getP.roomId = j[ID_JSON];
	return getP;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
	json j = createJson(buffer);
	JoinRoomRequest joinRoom;
	joinRoom.roomId = j[ID_JSON];
	return joinRoom;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
	json j = createJson(buffer);
	CreateRoomRequest createRoom;
	createRoom.answerTimeout = j[TIME];
	createRoom.maxUsers = j[MAX_USERS];
	createRoom.questionCount = j[QUESTION_COUNT];
	createRoom.roomName = j[NAME];
	return createRoom;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(std::vector<unsigned char> buffer)
{
	return SubmitAnswerRequest();
}
