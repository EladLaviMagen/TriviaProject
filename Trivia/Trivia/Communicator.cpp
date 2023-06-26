#include "Communicator.h"

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	

	while (true)
	{
		IRequestHandler* handler = m_handlerFactory.createLoginRequestHandler();
		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server
		SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted. Server and client can speak" << std::endl;
		m_clients[client_socket] = handler;
		//Creating a thread with the function that handles the conversation with the client
		std::thread t(std::ref(*this), client_socket);
		//Detaching it, as it works separately from program
		t.detach();
	}
}

void Communicator::handleNewClient(SOCKET sock)
{
	IRequestHandler* hold = nullptr;
	try
	{
		while (true)
		{
			std::string dataToSend = "";
			std::string biNumber = Helper::getStringPartFromSocket(sock, CODE);//getting the code from the msg
			int code = std::stoi(biNumber, 0, 2);
			int size = 0;
			std::string keep = "";
			std::string biSize = "";

			for (int i = 0; i < SIZE / 8; i++)//getting the size of the data
			{
				size *= 10;
				keep = Helper::getStringPartFromSocket(sock, CODE);
				size += std::stoi(keep, 0, 2);
				biSize += keep;

			}
			std::string msg = Helper::getStringPartFromSocket(sock, 8 * size);//getting the data
			std::vector<byte> buffer;
			for (int i = 0; i < biSize.length(); i++)
			{
				buffer.push_back(biSize[i]);
			}
			for (int i = 0; i < msg.length(); i++)
			{
				buffer.push_back(msg[i]);
			}
			RequestInfo info = { code, buffer };
			if (m_clients[sock]->isRequestRelevant(info))//checking if request is relevant
			{
				RequestResult result = m_clients[sock]->handleRequest(info);
				hold = result.newHandler;
				if (m_clients[sock] != result.newHandler)//changing handler if needed
				{
					IRequestHandler* temp =  m_clients[sock];
					m_clients[sock] = result.newHandler;
					delete temp;
					
				}
				for (int i = 0; i < result.response.size(); i++)//entring to data to send the results
				{
					dataToSend += result.response[i];
				}
			}
			else//if the request is irrelevant
			{
				ErrorResponse err = { "Request irrelevant" };//sending an error response to client
				std::vector<unsigned char> response = JsonResponsePacketSerializer::serializeResponse(err);

				for (int i = 0; i < response.size(); i++)
				{
					dataToSend += response[i];
				}
			}
			Helper::sendData(sock, dataToSend);
		}
	}
	catch (std::exception ex)//if there is an error in the middle than catching it and handling
	{
		if (hold != nullptr)//if the handler is not null
		{
			//checking the user state and logging him out ;)
			RequestInfo check;
			check.id = LEAVEGAME;
			if (hold->isRequestRelevant(check))
			{
				RequestResult removal = hold->handleRequest(check);
				check.id = LOGOUT;
				RequestResult removal2 = removal.newHandler->handleRequest(check);
				delete removal.newHandler;
				delete removal2.newHandler;
			}
			check.id = LEAVEROOM;
			if (hold->isRequestRelevant(check))
			{
				RequestResult removal = hold->handleRequest(check);
				check.id = LOGOUT;
				RequestResult removal2 = removal.newHandler->handleRequest(check);
				delete removal.newHandler;
				delete removal2.newHandler;
			}
			check.id = CLOSEROOM;
			if (hold->isRequestRelevant(check))
			{
				RequestResult removal = hold->handleRequest(check);
				check.id = LOGOUT;
				RequestResult removal2 = removal.newHandler->handleRequest(check);
				delete removal.newHandler;
				delete removal2.newHandler;
			}
			check.id = LOGOUT;
			if (hold->isRequestRelevant(check))
			{
				RequestResult removal = hold->handleRequest(check);
				delete removal.newHandler;
			}
			delete hold;
		}
	}
}

void Communicator::startHandleRequest()
{
	std::thread startUp(std::ref(*this));
	startUp.detach();
}

void Communicator::operator() ()
{
	this->bindAndListen();
}

void Communicator::operator() (SOCKET sock)
{
	this->handleNewClient(sock);
}