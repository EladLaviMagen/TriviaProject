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

std::string str_to_bin_str(const std::string& str) {
	std::string binary_str = "";
	for (char c : str) {
		// Convert the character to its ASCII code and then to binary string
		binary_str += std::bitset<8>(c).to_string();
	}
	return binary_str;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	json buff;
	buff[MESSAGE] = err.message;
	std::string bufferStr = "";
	bufferStr += ERROR_CODE;
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

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	json buff;
	buff[STATUS] = log.status;
	std::string bufferStr = "";
	bufferStr += ERROR_CODE;
	std::string ser = buff.dump();
	int size = ser.length();
	std::string buffSize = int_to_bin_str(size);
	for (int i = buffSize.length(); i < 32; i++)
	{
		buffSize = '0' + buffSize;
	}
	std::cout << buffSize;
	bufferStr += buffSize + str_to_bin_str(ser);
	std::vector<unsigned char> output;
	for (int i = 0; i < bufferStr.length(); i++)
	{
		output.push_back(bufferStr[i]);
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
