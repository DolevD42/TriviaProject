#include "Game.h"
Question Game::getQuestionForUser(LoggedUser users)
{
	auto it = m_players.find(users);
	return it->second.currentQuestion;
}
void Game::submitAnswer(LoggedUser users, int answeriD)
{
	auto it = m_players.find(users);
	if (answeriD == it->second.currentQuestion.getCorrectAnswerIndex() + 1)
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
void Game::removePlayer(LoggedUser users)
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
