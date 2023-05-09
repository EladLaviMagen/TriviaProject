#pragma once
#include "Communicator.h"
class Server
{
public:
	Server() = default;
	void run();
	void operator() ();
private:
	Communicator m_comminicator;
	
};

