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
	std::vector<Game*> m_games;
	int _gameId;
public:
	GameManager(IDataBase* db);
	Game* CreateGame(Room* room);
	void deleteGame(int gameId);
	void EnterDbInfo(std::string userName, int CorrectAnswerCount, int WrongAnswerCount, float averageAnswerTime, int AnswersCount);
	Game* lastGame();
};