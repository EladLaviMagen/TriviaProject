#pragma once
#include "MyException.h"
class UserNotExistException : public MyException
{
public:
	UserNotExistException(std::string msg);
	virtual ~UserNotExistException() noexcept = default;
	virtual const char* what() const;
};

