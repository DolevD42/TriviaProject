#pragma once

#include <iostream>
#include <ostream>
#include <WinSock2.h>
#include <Windows.h>
#include <vector>
#include <thread>
#include <map>
#include "LoginRequestHandler.h"
#include "Helper.h"

class Communicator
{
public:
	Communicator();
	void startHandleRequests();

private:
	
	SOCKET m_serverSocket;
	std::vector<std::thread> _threadVector;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();

	void handleNewClient(SOCKET clientSocket);
};

