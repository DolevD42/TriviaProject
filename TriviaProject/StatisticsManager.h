#pragma once
#include "IDataBase.h"

class StatisticsManager
{
private:
	IDataBase* m_database;
public:
	std::vector<std::string> getUserStatistics(std::string userName);
	std::vector<std::string> getHighScore();
	std::map<std::string, std::string> getStatistics(std::string username) throw();
};