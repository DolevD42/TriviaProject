#include "Game.h"
Game::Game(Room room, std::vector<Question*> quest)//LoggedUser* User,unsigned int CorrectAnswerCount, unsigned int WrongAnswerCount, float averageAnswerTime)
{
	for (int i = 0; i < room.getAllLoggedUser().size(); i++) {
		struct GameData gamedata;
		gamedata.currentQuestion = m_questions[0];
		gamedata.averageAnswerTime = 0;
		gamedata.currentQuestion = 0;
		gamedata.WrongAnswerCount = 0;
		gamedata.playing = true;
		m_players.insert({ room.getAllLoggedUser()[i], gamedata });
	}
	m_questions = quest;
}
Question* Game::getQuestionForUser(LoggedUser* users)
{
	auto it = m_players.find(users);
	int place = it->second.WrongAnswerCount + it->second.CorrectAnswerCount;
	return m_questions[place];
}
void Game::submitAnswer(LoggedUser* users, int answeriD)
{
	auto it = m_players.find(users);
	int indx = it->second.currentQuestion->getCorrectAnswerIndex();
	if (answeriD == indx + 1)
	{
		it->second.CorrectAnswerCount += 1;
		
		//add the send right answer
	}
	else
	{
		it->second.WrongAnswerCount += 1;
		//add the send wrong answer
	}

}
void Game::removePlayer(LoggedUser* users)
{
	try
	{
		for(auto it :m_players)
		{
			if (it.first == users)
			{
				it.second.playing = false;
			}
		}
	}
	catch (const std::exception& e)
	{
		throw(e);
		return;
	}
}

int Game::getGameId()
{
	return m_gameId;
}
