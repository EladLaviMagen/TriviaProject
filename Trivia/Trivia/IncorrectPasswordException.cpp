#include "IncorrectPasswordException.h"

IncorrectPasswordException::IncorrectPasswordException(std::string msg) : MyException(msg)
{
}

const char* IncorrectPasswordException::what() const
{
	return m_message.c_str();
}
