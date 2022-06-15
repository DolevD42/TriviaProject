#pragma once
#include "Question.h"
#include "sqlite3.h"
#include <string>
#include <list>
class IDataBase
{
public:
	virtual bool doesUserExist(std::string userName) = 0;
	virtual bool doesPasswordMatch(std::string userName, std::string pass) = 0;
	virtual void addNewUser(std::string userName, std::string pass, std::string email) = 0;
	virtual std::list<Question*> getQuestions() = 0;
	virtual float getPlayerAverageAnswerTime(std::string id) = 0;
	virtual int  getNumOfCorrectAnswers(std::string id) = 0;
	virtual int  getNumOfTotalAnswers(std::string id) = 0;
	virtual int  getNumOfPlayerGames(std::string id) = 0;
	virtual std::vector<std::string> getAllUserName() = 0;
	virtual sqlite3* GetDb() = 0;
	virtual int insertNewGame() = 0;
	virtual void RemoveNewGame(int id) = 0;
};

