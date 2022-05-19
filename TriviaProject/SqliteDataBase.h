#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#include "IDataBase.h"
#include "sqlite3.h"
class SqliteDataBase :
    public IDataBase
{
public:
	virtual bool doesUserExist(std::string userName);
	virtual bool doesPasswordMatch(std::string userName, std::string pass);
	virtual void addNewUser(std::string userName, std::string pass, std::string email);
	virtual const std::list<Question> getQuestions(int id) override;
	virtual float getPlayerAverageAnswer(std::string id);
	virtual int  getNumOfCurrectAnswers(std::string id);
	virtual int  getNumOfTotalAnswers(std::string id);
	virtual int  getNumOfPlayerGames(std::string id);
private:
	char* _errMessage = nullptr;
	sqlite3* _db = nullptr;
	bool open();
};

