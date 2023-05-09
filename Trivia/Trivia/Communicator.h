#pragma once
#include <map>
#include <iostream>
#include <thread>
#include "LoginRequestHandler.h"
#include "Helper.h"
#include "JsonResponsePacketSerializer.h"

#define PORT 42069 
#define SIZE 32
#define CODE 8

class IRequestHandler;
class LoginRequestHandler;

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


