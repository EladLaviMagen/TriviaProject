#pragma once
#include "Communicator.h"
#include "SqliteDatabase.h"
#include "RequestHandlerFactory.h"
class Server
{
public:
	Server(RequestHandlerFactory handlerFactory);
	void run();
	void operator() ();
private:
	Communicator m_comminicator;
	RequestHandlerFactory m_handlerFactory;
	IDatabase* m_database;	
};

