#pragma once
#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include "IRequestHandler.h"
#include <iostream>

class Communicator
{
public:
	Communicator();
	void startHandleRequest();

private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	
	void bindAndListen();
	void handleNewClient(SOCKET sock);
};


