#include "RoomManager.h"

int RoomManager::id = 1;
RoomManager::RoomManager()
{
}
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
	try
	{
		return m_rooms[ID];
	}
	catch (std::exception ex)
	{
		throw RoomNotExist("fake");
	}
	
}

int RoomManager::assignID()
{
	int ret = this->id;
	this->id++;
	return ret;
}

int RoomManager::getID()
{
	return id;
}
