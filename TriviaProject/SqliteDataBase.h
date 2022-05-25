#pragma once

#include <string>
#include <stdio.h>
#include <iostream>

#include "sqlite3.h"

#include <list>
#include "IDataBase.h"

class SqliteDataBase :
    public IDataBase
{
public:
	SqliteDataBase();
	~SqliteDataBase();
	virtual bool doesUserExist(std::string userName);
	virtual bool doesPasswordMatch(std::string userName, std::string pass);
	virtual void addNewUser(std::string userName, std::string pass, std::string email);
	virtual std::list<Question*> getQuestions(int id);
	virtual float getPlayerAverageAnswerTime(std::string id);
	virtual int  getNumOfCurrectAnswers(std::string id);
	virtual int  getNumOfTotalAnswers(std::string id);
	virtual int  getNumOfPlayerGames(std::string id);
	int getUserID(std::string username);
	virtual sqlite3* GetDb();
private:
	char* _errMessage = nullptr;
	sqlite3* _db = nullptr;
	bool open();
	
	std::string _filename;
};


