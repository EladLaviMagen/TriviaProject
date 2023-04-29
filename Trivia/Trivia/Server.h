#pragma once
#include "Communicator.h"
#include <WinSock2.h>
class Server
{
public:
	Server();
	void run();
	void operator() ();
private:
	Communicator m_comminicator;
	
};

