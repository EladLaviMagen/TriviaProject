#pragma once
#include "IDatabase.h"
#include "Game.h"
#include <mutex>
#include "Room.h"
class GameManager
{
public:
	GameManager(IDatabase* data);
	Game createGame(Room room);
	void deleteGame(unsigned int gameId);
	Game& getGame(std::string name);

private:
	static std::mutex gamer_lock;
	IDatabase* m_database;
	std::vector<Game> m_games;
};

