#pragma once
#include "MyException.h"
class AccLoggedException : public MyException
{
public:
	AccLoggedException(std::string msg);
	virtual ~AccLoggedException() noexcept = default;
	virtual const char* what() const noexcept override;
};

