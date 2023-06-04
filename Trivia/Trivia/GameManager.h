#pragma once
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
class GameManager
{
public:
	GameManager(IDatabase* data);
	Game createGame(Room room);
	void deleteGame(unsigned int gameId);
private:
	IDatabase* m_database;
	std::vector<Game> m_games;
};

