#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* data)
{
	m_database = data;
}

std::vector<std::string> StatisticsManager::getHighScore()
{
	return m_database->getHighScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string userName)
{
	std::vector<std::string> stats;
	stats.push_back(std::to_string(m_database->getNumOfCorrectAnswer(userName)));
	stats.push_back(std::to_string(m_database->getNumOfTotalAnswers(userName)));
	stats.push_back(std::to_string(m_database->getPlayerAverageAnswerTime(userName)));
	stats.push_back(std::to_string(m_database->getNumOfPlayerGames(userName)));
	return stats;
}
