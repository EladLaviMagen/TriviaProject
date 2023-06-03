#pragma once
#include "MyException.h"
class RoomNotExist : public MyException
{
public:
	RoomNotExist(std::string msg);
	virtual ~RoomNotExist() noexcept = default;
	virtual const char* what() const noexcept override;

};

