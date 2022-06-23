#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <stdio.h>



class LoggedUser
{
public:
	LoggedUser(std::string userName, SOCKET socket);
	std::string getUsername();
	SOCKET getSocket();
private:
	std::string m_username;
	SOCKET m_socket;
};

