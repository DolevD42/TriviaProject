#include "StatisticsManager.h"
#include <sys/stat.h>
#include <algorithm>


bool pairCompare(const std::pair<int, std::string>& first, const std::pair<int, std::string>& second);
bool pairCompare(const std::pair<int, std::string>& first, const std::pair<int, std::string>& second)
{
	return first.first > second.first;
}

StatisticsManager::StatisticsManager(IDataBase* db)
{
	m_database = db;
}

StatisticsManager::~StatisticsManager()
{
	if (m_database)
	{
		delete m_database;
	}
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string userName)
{
	std::vector<std::string> stats;
	stats.push_back(std::to_string(this->m_database->getPlayerAverageAnswerTime(userName)));
	stats.push_back(std::to_string(this->m_database->getNumOfTotalAnswers(userName)));
	stats.push_back(std::to_string(this->m_database->getNumOfPlayerGames(userName)));
	stats.push_back(std::to_string(this->m_database->getNumOfCurrectAnswers(userName)));
	return stats;
}

std::vector<std::string> StatisticsManager::getHighScore()
{ 
	std::vector<std::string> usernamesBestScores;
	std::vector<std::string> usernames = m_database->getAllUserName();
	int NumCurrctAnswers;
	int Answers;
	float avgAnswer;
	std::vector<std::pair<float, std::string>> bestScores;
	try
	{
		for (auto username : usernames)
		{
			NumCurrctAnswers = m_database->getNumOfCurrectAnswers(username);
			Answers = m_database->getNumOfTotalAnswers(username);
			avgAnswer = m_database->getPlayerAverageAnswerTime(username);
			std::pair<float, std::string> userScore(((float(NumCurrctAnswers)) / (float(Answers) * avgAnswer)), username);
			bestScores.push_back(userScore);
		}
		std::sort(bestScores.begin(), bestScores.end(), pairCompare);
		for (auto & element : bestScores)
		{
			usernamesBestScores.push_back(element.second);
		}
		return usernamesBestScores;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return usernamesBestScores;
	}
}
