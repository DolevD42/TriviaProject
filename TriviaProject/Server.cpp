#include "Server.h"

void Server::run()
{
	Communicator communicator = Communicator();
	m_communicator = communicator;
	std::thread t_connector(&Communicator::startHandleRequests, &m_communicator);
	t_connector.detach();
	std::string command = "";
	while (command != "EXIT")
	{
		std::cin >> command;
	}
}
