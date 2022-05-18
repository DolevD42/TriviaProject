#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <vector>
#include <thread>
#include <map>
#include <string>
#include <iostream>
#include <ostream>
#include <WinSock2.h>
#include "LoginRequestHandler.h"
#include "Helper.h"
#include <Windows.h>
#include "RequestHandlerFactory.h"
#define ZERO 126
class Communicator
{
public:
	Communicator(RequestHandlerFactory* factory);
	void startHandleRequests();

private:
	RequestHandlerFactory* m_handlerFactory;
	SOCKET m_serverSocket;
	std::vector<std::thread> _threadVector;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();

	void handleNewClient(SOCKET clientSocket);
};

