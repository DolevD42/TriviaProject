#include "Game.h"
Game::Game(LoggedUser* User,unsigned int CorrectAnswerCount, unsigned int WrongAnswerCount, float averageAnswerTime)
{
	float averageAnswerTime2 = averageAnswerTime;
	int CorrectAnswerCount2 = CorrectAnswerCount;
	int WrongAnswerCount2 = WrongAnswerCount;
	Question* currentQuestion2 = this->getQuestionForUser(User);
	struct GameData req;
	req.averageAnswerTime = averageAnswerTime2;
	req.CorrectAnswerCount = CorrectAnswerCount2;
	req.currentQuestion = currentQuestion2;
	req.WrongAnswerCount = WrongAnswerCount2;
	m_players.insert({ User, req });
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
		m_players.erase(users);
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
