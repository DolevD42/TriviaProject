#include "GameManager.h"
GameManager::GameManager(IDataBase* db): m_database(db)
{
}
Game* GameManager::CreateGame(Room* room)
{
	try
	{
		
		_gameId = m_database->insertNewGame();
		if (_gameId == -1)
		{
			throw std::exception("Couldn't insert game into the database");
		}
		std::vector<Question*> vectAllQuestions;
		std::vector<Question*> vect;

		for (Question* quest : m_database->getQuestions())
		{
			vectAllQuestions.push_back(quest);
		}
		for (int i = 0; i < room->getRoomData().numOfQuestionInGame; i++)
		{
			vect.push_back(vectAllQuestions[i]);
		}
		Game* newGame = new Game(room, vect);
		m_games.push_back(newGame);
		return newGame;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void GameManager::deleteGame(int gameId)
{
	m_database->RemoveNewGame(gameId);
	int curGameId;
	int i = 0;
	for (auto it = m_games.begin();it != m_games.end(); it++)
	{
		i++;
		curGameId = m_games[i]->getGameId();
		if (curGameId = gameId)
		{
			it = m_games.erase(it);
			break;
		}
	}
}

void GameManager::EnterDbInfo(std::string userName, int CorrectAnswerCount, int WrongAnswerCount, float averageAnswerTime, int AnswersCount)
{
	m_database->InsertPlayerResults(userName, CorrectAnswerCount, WrongAnswerCount, averageAnswerTime, AnswersCount);
}

Game* GameManager::lastGame()
{
	return m_games[m_games.size()-1];
}
