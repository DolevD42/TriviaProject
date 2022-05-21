#pragma once
#include "IDataBase.h"
#include "LoggedUser.h"
class StatisticsManager
{
private:
	IDataBase* m_database;
public:
	std::vector<std::string> getUserStatistics(std::string userName);
	std::vector<std::string> getHighScore();
};