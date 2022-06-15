#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
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
	virtual int  getNumOfCorrectAnswers(std::string id);
	virtual int  getNumOfTotalAnswers(std::string id);
	virtual int  getNumOfPlayerGames(std::string id);
	virtual std::vector<std::string> getAllUserName();
	virtual sqlite3* GetDb();
	virtual int insertNewGame();
	virtual void RemoveNewGame(int id);
private:
	char* _errMessage = nullptr;
	sqlite3* _db = nullptr;
	bool open();
	int _currGameId;
	std::string _filename = "TriviaDB.sqlite";
};


