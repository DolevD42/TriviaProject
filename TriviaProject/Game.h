#pragma once
#include "SqliteDataBase.h"
#include "IDataBase.h"
#include "LoggedUser.h"
#include "Question.h"
#include <map>
#include "Room.h"

struct GameData {
	Question* currentQuestion;
	unsigned int CorrectAnswerCount;
	unsigned int WrongAnswerCount;
	float averageAnswerTime;
	bool playing;
};
class Game
{
private:
	std::vector<Question*> m_questions;
	std::map<LoggedUser*, GameData> m_players;
	int m_gameId;
public:
	Game(Room* room, std::vector<Question*> quest);
	Question* getQuestionForUser(LoggedUser* users);
	int submitAnswer(LoggedUser* users,int answeriD, float timePerAns);
	void removePlayer(LoggedUser* users);
	std::map<LoggedUser*, GameData> getData();
	int getGameId();
	void changeUserStatus(LoggedUser* user, bool value);
};
