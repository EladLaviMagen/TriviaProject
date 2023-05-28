#pragma once
#include "LoggedUser.h"
#include <vector>

typedef struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestions;
	unsigned int timePerQuestion;
	unsigned int isActive;
};

class Room
{
public:
	Room(LoggedUser user, RoomData data);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	RoomData getData();
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
