#include "Server.h"

Server::Server(RequestHandlerFactory handlerFactory) : m_handlerFactory(handlerFactory) , m_comminicator(handlerFactory)
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
