#include "GameManager.h"

std::mutex GameManager::gamer_lock;
//C'tor
GameManager::GameManager(IDatabase* data)
{
	m_games = new std::vector<Game*>();//creating vector of all games
	m_database = data;//getting database
}



Game* GameManager::createGame(Room room)
{
	std::vector<LoggedUser>* vec = new std::vector<LoggedUser>();//creating vector of logged users to game
	std::vector<std::string> players = room.getAllUsers();//adding to him all the users from room
	for (int i = 0; i < players.size(); i++)
	{
		vec->push_back(LoggedUser(players[i]));
	}
	Game* game = new Game(m_database->getQuestions((room.getData()).numOfQuestions), vec, (room.getData()).timePerQuestion);//creating new game
	{
		std::lock_guard<std::mutex> locker(gamer_lock);
		m_games->push_back(game);//adding him to the vector of games
	}
	
	return game;//returning game
}

void GameManager::deleteGame(unsigned int gameId)
{
	if (m_games->size() != 0)//if there are games
	{
		{
			std::lock_guard<std::mutex> locker(gamer_lock);
			for (auto it = m_games->begin(); it != m_games->end(); it++)//checking till we find the correct game and deleting him
			{	
				if ((*it)->getId() == gameId)
				{
					m_games->erase(it);
					return;
				}
			}
		}
		
	}
}
//update the scores of player from his last game
void GameManager::updateScores(PlayerResults data)
{
	m_database->updateScores(data);
}

Game* GameManager::getGame(std::string name)
{
	{
		std::lock_guard<std::mutex> locker(gamer_lock);
		for (auto i = m_games->begin(); i != m_games->end(); i++)//going trough games till we find he wanted one 
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
