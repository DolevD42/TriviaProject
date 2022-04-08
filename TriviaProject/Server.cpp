#include "Server.h"

void Server::run()
{
	Communicator* communicator = new Communicator();
	//m_communicator = communicator;
	std::thread t_connector(&Communicator::startHandleRequests, communicator);
	t_connector.detach();
	std::string command = "";
	while (command != "EXIT")
	{
		std::cin >> command;
	}
}
