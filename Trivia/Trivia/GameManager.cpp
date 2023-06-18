#include "GameManager.h"

GameManager::GameManager(IDatabase* data)
{
	m_database = data;
}

Game GameManager::createGame(Room room)
{
	std::vector<LoggedUser> vec;
	std::vector<std::string> players = room.getAllUsers();
	for (int i = 0; i < players.size(); i++)
	{
		vec.push_back(LoggedUser(players[i]));
	}
	Game game = Game(m_database->getQuestions((room.getData()).timePerQuestion), vec, (room.getData()).timePerQuestion);
	m_games.push_back(game);
	return game;
}

void GameManager::deleteGame(unsigned int gameId)
{
	if (m_games.size() != 0)
	{
		for (auto it = this->m_games.begin(); it != this->m_games.end(); it++)
		{
			if (it->getId() == gameId)
			{
				m_games.erase(it);
			}
		}
	}
}
