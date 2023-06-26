#include "AccLoggedException.h"

AccLoggedException::AccLoggedException(std::string msg) : MyException(msg)
{
}

const char* AccLoggedException::what() const noexcept
{
	return m_message.c_str();
}
