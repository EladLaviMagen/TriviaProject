#include "Communicator.h"

Communicator::Communicator()
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
		IRequestHandler* handler = new LoginRequestHandler();
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
	while (true)
	{
		std::string dataToSend = "";
		std::string biNumber = Helper::getStringPartFromSocket(sock, CODE);
		int code = std::stoi(biNumber, 0, 2);
		std::string biSize = Helper::getStringPartFromSocket(sock, SIZE);
		int size = std::stoi(biSize, 0, 2);
		std::string msg = Helper::getStringPartFromSocket(sock, 8 * size);
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
		if (m_clients[sock]->isRequestRelevant(info))
		{
			RequestResult result = m_clients[sock]->handleRequest(info);
			m_clients[sock] = result.newHandler;
			for (int i = 0; i < result.response.size(); i++)
			{
				dataToSend += result.response[i];
			}
			
			
		}
		else
		{
			ErrorResponse err = { "Request irrelevant" };
			std::vector<unsigned char> response = JsonResponsePacketSerializer::serializeResponse(err);
			
			for (int i = 0; i < response.size(); i++)
			{
				dataToSend += response[i];
			}
			
		}
		Helper::sendData(sock, dataToSend);
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