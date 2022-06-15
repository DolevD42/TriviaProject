#pragma once
#include "SqliteDataBase.h"
#include "IDataBase.h"
#include "Game.h"
#include "LoggedUser.h"
#include "Room.h"
class GameManager
{
private:
	IDataBase* m_database;
	std::vector<Game> m_games;
	int _gameId;
public:
	Game CreateGame(Room room);
	void deleteGame(int gameId);
};