#pragma once
#include "SqliteDataBase.h"
#include "IDataBase.h"
#include "LoggedUser.h"
#include "GameData.h"
#include "Question.h"
#include <map>
class GameManager
{
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;
public:
	Question getQuestionForUser(LoggedUser users);
	void submitAnswer(LoggedUser users,int answeriD);
	void removePlayer(LoggedUser users);
};