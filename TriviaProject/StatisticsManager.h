#pragma once
#include "SqliteDataBase.h"
#include "IDataBase.h"
#include "LoggedUser.h"
class StatisticsManager
{
private:
	IDataBase* m_database;
public:
	StatisticsManager(IDataBase* db);
	~StatisticsManager();
	std::vector<std::string> getUserStatistics(std::string userName);
	std::vector<std::string> getHighScore();
};