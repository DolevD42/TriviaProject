// TriviaProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <thread>
#include <iostream>
#include "Server.h"
int main()
{
    Server myServer;
    std::thread mainThread(&Server::run, &myServer);
    mainThread.join();
}
