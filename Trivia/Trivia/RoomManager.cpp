#include "RoomManager.h"

int id = 1;
void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	this->m_rooms[id] = Room(user, data);
}

void RoomManager::deleteRoom(int ID)
{
	m_rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(int ID)
{
	return (m_rooms[ID].getData()).isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
	{
		rooms.push_back(it->second.getData());
	}
	return rooms;
}

Room& RoomManager::getRoom(int ID)
{
	return m_rooms[ID];
}
