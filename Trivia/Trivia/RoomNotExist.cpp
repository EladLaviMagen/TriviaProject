#include "RoomNotExist.h"

RoomNotExist::RoomNotExist(std::string msg) : MyException(msg)
{}

const char* RoomNotExist::what() const noexcept
{
	return m_message.c_str();
}