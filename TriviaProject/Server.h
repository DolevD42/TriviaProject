#pragma once
#include <thread>
#include <iostream>
#include <ostream>
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "IDataBase.h"
class Server
{
public:
	Server();
	void run();
private:
	IDataBase* m_database;
	RequestHandlerFactory* m_handlerFactory;
	Communicator* m_communicator;
};

