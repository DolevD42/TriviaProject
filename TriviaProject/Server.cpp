#include "Server.h"

Server::Server()
{
	this->m_database = new SqliteDataBase();
	this->m_handlerFactory = new RequestHandlerFactory(this->m_database);
}

void Server::run()
{
	Communicator* communicator = new Communicator(this->m_handlerFactory);
	m_communicator = communicator;
	std::thread t_connector(&Communicator::startHandleRequests, communicator);
	t_connector.detach();
	std::string command = "";
	while (command != "EXIT")
	{
		std::cin >> command;
	}
}
