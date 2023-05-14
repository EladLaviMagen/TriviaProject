#include "AccLoggedException.h"

AccLoggedException::AccLoggedException(std::string msg) : MyException(msg)
{
}

const char* AccLoggedException::what() const
{
	return m_message.c_str();
}
