#pragma once
#include "SqliteDataBase.h"
#include "IDataBase.h"
#include "Game.h"
#include "LoggedUser.h"
class GameManager
{
private:
	IDataBase* m_database;
	std::vector<Game> m_games;
public:
	Game CreateGame(std::string userName);
	void deleteGame();
};