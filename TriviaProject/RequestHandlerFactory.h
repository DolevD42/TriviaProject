#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "StatisticsManager.h"
class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class RequestHandlerFactory
{
	LoginManager* m_loginManager;
	RoomManager* m_roomManager;
	IDataBase* m_database;
	StatisticsManager* m_statistics;

public:
	RequestHandlerFactory(IDataBase* db);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler(SOCKET socket);
	MenuRequestHandler* createMenuRequestHandler(SOCKET socket, LoggedUser* user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(SOCKET socket, LoggedUser* user, Room* room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(SOCKET socket, LoggedUser* user, Room* room);

	RoomManager* getRoomManager() { return m_roomManager; };
	LoginManager* getLoginManager() { return m_loginManager; };
	StatisticsManager* getStatisticsManager() { return m_statistics;  };

};
