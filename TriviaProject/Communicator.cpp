#include "Communicator.h"
#define PORT 8876

Communicator::Communicator()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

void Communicator::startHandleRequests()
{
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		bindAndListen();
	}
}

void Communicator::bindAndListen()
{
	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	_threadVector.push_back(std::thread(&Communicator::handleNewClient, this, client_socket));
	auto it = _threadVector.rbegin();
	it->detach();


	// the function that handle the conversation with the client
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	std::pair< SOCKET, IRequestHandler* > pair;
	pair.first = clientSocket;
	LoginRequestHandler* log = new LoginRequestHandler();
	pair.second = log;
	m_clients.insert(pair);
	try
	{
		Helper::sendData(clientSocket, "Hello");

		std::string msg = Helper::getStringPartFromSocket(clientSocket, 5);
		std::cout << msg << std::endl;
	}
	catch (const std::exception&)
	{

	}
	
}
