#include "Server.h"

Server::Server(RequestHandlerFactory handlerFactory) : m_handlerFactory(handlerFactory) , m_comminicator(handlerFactory)
{
	m_database = new SqliteDatabase();
}
void Server::run()
{
	m_comminicator.startHandleRequest();
}

void Server::operator() ()
{
	run();
}
