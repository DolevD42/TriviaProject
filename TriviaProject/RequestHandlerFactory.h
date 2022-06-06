#pragma once
#include <string>
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
class LoginRequestHandler;
class MenuRequestHandler;
class RequestHandlerFactory
{
	LoginManager* m_loginManager;
	RoomManager* m_roomManager;
	IDataBase* m_database;
	StatisticsManager* m_statistics;

public:
	RequestHandlerFactory(IDataBase* db);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	RoomManager* getRoomManager() { return m_roomManager; };
	LoginManager* getLoginManager() { return m_loginManager; };
	StatisticsManager* getStatisticsManager() { return m_statistics;  };

};
