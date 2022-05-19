#pragma once
#include "Question.h"
#include <string>
#include <list>
class IDataBase
{
public:
	virtual bool doesUserExist(std::string userName) = 0;
	virtual bool doesPasswordMatch(std::string userName, std::string pass) = 0;
	virtual void addNewUser(std::string userName, std::string pass, std::string email) = 0;
	virtual const std::list<Question> getQuestions(int id) = 0;
	virtual float getPlayerAverageAnswer(std::string id) = 0;
	virtual int  getNumOfCurrectAnswers(std::string id) = 0;
	virtual int  getNumOfTotalAnswers(std::string id) = 0;
	virtual int  getNumOfPlayerGames(std::string id) = 0;
};

