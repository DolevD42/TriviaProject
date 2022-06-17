#include "GameManager.h"
Game GameManager::CreateGame(Room room)
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
		for (int i = 0; i < room.getRoomData().numOfQuestionInGame; i++)
		{
			vect.push_back(vectAllQuestions[i]);
		}
		Game newGame = Game(room, vect);
		m_games.push_back(newGame);
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
	for (std::vector<Game>::iterator it = m_games.end();it != m_games.begin();) 
	{
		curGameId = it->getGameId();
		if (curGameId = gameId)
		{
			it = m_games.erase(it);
			break;
		}
	}
}
