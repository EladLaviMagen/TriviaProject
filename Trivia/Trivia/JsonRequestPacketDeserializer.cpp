#include "JsonRequestPacketDeserializer.h"


LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	int size = int(buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3]);
	for (int i = 0; i < 4;i++)
	{
		buffer.erase(buffer.begin());
	}

}