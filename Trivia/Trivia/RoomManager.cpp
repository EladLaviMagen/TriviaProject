#include "RoomManager.h"

int RoomManager::id = 1;
std::mutex RoomManager::room_lock;
RoomManager::RoomManager()
{
}
void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	this->m_rooms[id] = Room(user, data);
}

void RoomManager::deleteRoom(int ID)
{
	{
		std::lock_guard<std::mutex> locker(room_lock);
		m_rooms.erase(ID);
	}
	
}

unsigned int RoomManager::getRoomState(int ID)
{
	{
		std::lock_guard<std::mutex> locker(room_lock);
		return (m_rooms[ID].getData()).isActive;
	}
	
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	if(m_rooms.size() != 0)
	{
		{
			std::lock_guard<std::mutex> locker(room_lock);
			for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
			{
				rooms.push_back(it->second.getData());
			}
		}	
	}
	return rooms;
}

Room& RoomManager::getRoom(int ID)
{
	{
		std::lock_guard<std::mutex> locker(room_lock);
		return m_rooms[ID];
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
