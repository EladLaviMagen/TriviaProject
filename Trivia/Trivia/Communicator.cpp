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

	//For now, while there is nothing
	IRequestHandler* dummy = nullptr;

	while (true)
	{
		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server
		SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted. Server and client can speak" << std::endl;
		m_clients[client_socket] = dummy;
		//Creating a thread with the function that handles the conversation with the client
		std::thread t(std::ref(*this), client_socket);
		//Detaching it, as it works separately from program
		t.detach();
	}
}

void Communicator::handleNewClient(SOCKET sock)
{
	std::string msg = "Hello";
	Helper::sendData(sock, msg);
	std::string ret = Helper::getStringPartFromSocket(sock, 5);
	std::cout << ret << std::endl;
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