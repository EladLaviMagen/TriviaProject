#include "Server.h"

Server::Server()
{
	
}
void Server::run()
{
	m_comminicator.startHandleRequest();
}

void Server::operator() ()
{
	run();
}
