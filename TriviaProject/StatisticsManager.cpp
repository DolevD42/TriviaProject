#include "StatisticsManager.h"

std::vector<std::string> StatisticsManager::getUserStatistics(std::string userName)
{
	return std::vector<std::string>();
}

std::vector<std::string> StatisticsManager::getHighScore()
{ 
	std::vector<std::vector<std::string>> highScores;
	std::vector<std::string> toReturn;
	highScores.push_back(std::vector<std::string>());
	highScores[0].push_back("score");//adding the columns to search for
	highScores[0].push_back("user");
	highScores = callbackUser("SELECT score, user FROM Highscores;", highScores);
	for (unsigned int i = 0; i < highScores.size(); i++) {
		LoggedUser a(highScores[i][1]);
		toReturn.insert(std::pair<LoggedUser, int>(LoggedUser(highScores[i][1]), std::stoi(highScores[i][0])));
	}
	return toReturn;

}
