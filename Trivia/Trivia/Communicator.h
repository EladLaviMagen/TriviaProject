#pragma once
#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include "IRequestHandler.h"
#include <iostream>
#include <thread>
#include "LoginRequestHandler.h"
#include "Helper.h"
#include "JsonResponsePacketSerializer.h"

#define PORT 42069 
#define SIZE 32
#define CODE 8

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


