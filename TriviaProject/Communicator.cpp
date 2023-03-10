#include "Communicator.h"
#define PORT 8876

Communicator::Communicator(RequestHandlerFactory* factory)
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	this->m_handlerFactory = factory;
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
	std::string recvMsg;
	std::string sendMsg;
	std::vector<char> vectMsg;
	RequestInfo reqInfo;
	RequestResult reqRes;
	int code;
	int msgLen;
	int num;
	std::pair< SOCKET, IRequestHandler* > pair;
	pair.first = clientSocket;

	LoginRequestHandler* log = m_handlerFactory->createLoginRequestHandler(clientSocket);
	pair.second = log;
	m_clients.insert(pair);
	try
	{
		while (true)
		{
			msgLen = 0;
			recvMsg = Helper::getStringPartFromSocket(clientSocket, 5);
			code = (int)recvMsg[0];
			for (int i = 0; i < 4; i++)
			{
				num = (int)recvMsg[4 - i];
				if (num == ZERO)
				{
					num = 0;
				}
				if (i == 0)
				{
					msgLen += num;
				}
				else
				{
					msgLen += num * pow(256, i);
				}
			}
			recvMsg = Helper::getStringPartFromSocket(clientSocket, msgLen);
			//std::cout << recvMsg << std::endl;
			reqInfo.buffer = Helper::fromStringToVector(recvMsg);
			reqInfo.id = code;
			reqInfo.recievedTime = std::time(0);
			reqRes = m_clients[clientSocket]->handleRequest(reqInfo); //important
			if (m_clients[clientSocket] != reqRes.newHandler)
			{
				delete m_clients[clientSocket];
			}
			m_clients[clientSocket] = reqRes.newHandler;
			sendMsg = Helper::fromVectToString(reqRes.response);
			std::cout << (int)sendMsg[0] << std::endl;
			Helper::sendData(clientSocket, sendMsg);
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	
}
