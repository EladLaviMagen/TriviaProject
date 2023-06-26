#include "UserNotExistException.h"
UserNotExistException::UserNotExistException(std::string msg) : MyException(msg)
{
}

const char* UserNotExistException::what() const noexcept
{
	return m_message.c_str();
}