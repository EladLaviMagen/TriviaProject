#pragma once
#include "SqliteDatabase.h"
#include <vector>
class StatisticsManager
{
public:
	StatisticsManager() = default;
	StatisticsManager(IDatabase* data);
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string userName);
private:
	IDatabase* m_database;
};

