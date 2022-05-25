#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataBase* db)
{
	m_loginManager = new LoginManager(db);
	m_roomManager = new RoomManager();
	m_database = db;
	m_statistics = new StatisticsManager(db);
}



RequestHandlerFactory::~RequestHandlerFactory()
{
	if (m_database)
	{
		delete m_database;
	}
	if (m_loginManager)
	{
		delete m_loginManager;
	}
	if (m_roomManager)
	{
		delete m_roomManager;
	}
	if (m_statistics)
	{
		delete m_statistics;
	}
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(m_loginManager, this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	return new MenuRequestHandler(m_roomManager, m_statistics, this);
}
