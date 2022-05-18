#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataBase* db)
{
	m_loginManager = new LoginManager(db);
	m_database = db;
}

RequestHandlerFactory::RequestHandlerFactory()
{
	m_loginManager = new LoginManager();
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete m_loginManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(m_loginManager, this);
}
