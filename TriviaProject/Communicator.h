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

