#pragma once
#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include "IRequestHandler.h"
#include <iostream>
#include <thread>
#include "LoginRequestHandler.h"
#include "Helper.h"

#define PORT 42069 

class Communicator
{
public:
	void operator() ();
	void operator() (SOCKET sock);
	Communicator();
	void startHandleRequest();

private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET sock);
	
};


