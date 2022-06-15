#pragma once
#include "SqliteDataBase.h"
#include "IDataBase.h"
#include "LoggedUser.h"
#include "Question.h"
#include <map>

struct GameData {
	Question* currentQuestion;
	unsigned int CorrectAnswerCount;
	unsigned int WrongAnswerCount;
	float averageAnswerTime;
};
class Game
{
private:
	std::vector<Question*> m_questions;
	std::map<LoggedUser*, GameData> m_players;
	int m_gameId;
public:
	Game(LoggedUser* User, unsigned int CorrectAnswerCount, unsigned int WrongAnswerCount, float averageAnswerTime);
	Question* getQuestionForUser(LoggedUser* users);
	void submitAnswer(LoggedUser* users,int answeriD);
	void removePlayer(LoggedUser* users);
	int getGameId();
};
