#pragma once
#include "SqliteDataBase.h"
#include "IDataBase.h"
#include "LoggedUser.h"
#include "Question.h"
#include <map>
typedef struct GameData {
	Question currentQuestion;
	unsigned int CorrectAnswerCount;
	unsigned int WrongAnswerCount;
	float averageAnswerTime;
} GameData;

class Game
{
private:
	std::vector<Question*> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;
public:
	Question getQuestionForUser(LoggedUser users);
	void submitAnswer(LoggedUser users,int answeriD);
	void removePlayer(LoggedUser users);
};