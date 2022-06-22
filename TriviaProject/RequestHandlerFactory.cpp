#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataBase* db)
{
	m_loginManager = new LoginManager(db);
	m_roomManager = new RoomManager();
	m_database = db;
	m_statistics = new StatisticsManager(db);
	m_gameManager = new GameManager(db);
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

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler(SOCKET socket)
{
	return new LoginRequestHandler(m_loginManager, this, socket);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(SOCKET socket, LoggedUser* user)
{
	return new MenuRequestHandler(m_roomManager, m_statistics, this, user ,socket);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(SOCKET socket, LoggedUser* user, Room* room)
{
	return new RoomAdminRequestHandler(m_roomManager, room, this, user, socket);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(SOCKET socket, LoggedUser* user, Room* room)
{
	return new RoomMemberRequestHandler(m_roomManager, room, this, user, socket);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(SOCKET socket, LoggedUser* user, Room* room)
{
	Game* game = m_gameManager->CreateGame(*room);
	return new GameRequestHandler(m_gameManager, game, this, user, socket);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(SOCKET socket, LoggedUser* user)
{
	return new GameRequestHandler(m_gameManager, m_gameManager->lastGame(), this, user, socket);
}
