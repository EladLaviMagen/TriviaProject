#include "Server.h"


void Server::run()
{
	m_comminicator.startHandleRequest();
}

void Server::operator() ()
{
	run();
}
