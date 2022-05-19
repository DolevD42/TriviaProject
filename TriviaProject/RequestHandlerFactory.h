#pragma once
#include <string>
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "StatisticsManager.h"
class LoginRequestHandler;

class RequestHandlerFactory
{
	LoginManager* m_loginManager;
	IDataBase* m_database;
	StatisticsManager m_statistics;
public:
	RequestHandlerFactory(IDataBase* db);
	RequestHandlerFactory();
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager() { return *m_loginManager; };
	StatisticsManager& getStatisticsManager();

};
