#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(SqliteDataBase* db)
{
	m_loginManager = new LoginManager(db);
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
