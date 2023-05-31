#pragma once
#include "MyException.h"
class IncorrectPasswordException : public MyException
{
public:
	IncorrectPasswordException(std::string msg);
	virtual ~IncorrectPasswordException() noexcept = default;
	virtual const char* what() const noexcept override;
};

