#include "GameManager.h"

std::mutex GameManager::gamer_lock;
GameManager::GameManager(IDatabase* data)
{
	m_games = new std::vector<Game*>();
	m_database = data;
}

Game* GameManager::createGame(Room room)
{
	std::vector<LoggedUser>* vec = new std::vector<LoggedUser>();
	std::vector<std::string> players = room.getAllUsers();
	for (int i = 0; i < players.size(); i++)
	{
		vec->push_back(LoggedUser(players[i]));
	}
	Game* game = new Game(m_database->getQuestions((room.getData()).timePerQuestion), vec, (room.getData()).timePerQuestion);
	{
		std::lock_guard<std::mutex> locker(gamer_lock);
		m_games->push_back(game);
	}
	
	return game;
}

void GameManager::deleteGame(unsigned int gameId)
{
	if (m_games->size() != 0)
	{
		{
			std::lock_guard<std::mutex> locker(gamer_lock);
			for (auto it = m_games->begin(); it != m_games->end(); it++)
			{	
				if ((*it)->getId() == gameId)
				{
					m_games->erase(it);
				}
			}
		}
		
	}
}

Game* GameManager::getGame(std::string name)
{
	{
		std::lock_guard<std::mutex> locker(gamer_lock);
		for (auto i = m_games->begin(); i != m_games->end(); i++)
		{
			for (auto it = (*i)->getPlayers()->begin(); it != (*i)->getPlayers()->end(); it++)
			{
				if (it->first == name)
				{
					return *i;
				}
			}
		}
	}
	
}
