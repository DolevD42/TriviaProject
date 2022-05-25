#include "StatisticsManager.h"
#include <sys/stat.h>
#include <algorithm>


bool pairCompare(const std::pair<int, string>& first, const std::pair<int, string>& second);
bool pairCompare(const std::pair<int, string>& first, const std::pair<int, string>& second)
{
	return first.first > second.first;
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
	std::vector<string> usernamesBestScores;
	sqlite3* _db = m_database->GetDb();
	int NumCurrctAnswers;
	int Answers;
	float avgAnswer;
	std::vector<std::pair<float, string>> bestScores;
	try
	{
		
		string sqlStatement = "FROM statistics SELECT usernames SEARCH *";
		sqlite3_stmt* stmt;
		if (sqlite3_prepare_v2(_db, sqlStatement.c_str(), strlen(sqlStatement.c_str()) + 1, &stmt, NULL) != SQLITE_OK)
			throw std::exception("error reading info");
		while (1)
		{
			int s;

			s = sqlite3_step(stmt);//get first row
			if (s == SQLITE_ROW)
			{
				string username = (char*)sqlite3_column_text(stmt, 0);
				NumCurrctAnswers = m_database->getNumOfCurrectAnswers(username);
				Answers = m_database->getNumOfTotalAnswers(username);
				avgAnswer = m_database->getPlayerAverageAnswerTime(username);
				std::pair<float, string> userScore((float(NumCurrctAnswers)) / (float(Answers) * avgAnswer), username);
				bestScores.push_back(userScore);
				
			}
			else if (s == SQLITE_DONE)
			{
				break;
			}
			else
			{
				sqlite3_finalize(stmt);
				throw std::exception("error reading info");
			}
		}
		std::sort(bestScores.begin(), bestScores.end(), pairCompare);
		sqlite3_finalize(stmt);
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
