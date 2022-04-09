// TriviaProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment (lib, "ws2_32.lib")
#include <thread>
#include <iostream>
#include "Server.h"
#include "WSAInitializer.h"
int main()
{
	try
	{

		WSAInitializer wsaInit;
		Server myServer;

		std::thread mainThread(&Server::run, &myServer);
		mainThread.join();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
    
}
