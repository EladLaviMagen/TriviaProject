#include "RoomManager.h"

int RoomManager::id = 1;
std::mutex RoomManager::room_lock;

RoomManager::RoomManager()
{
	m_rooms = new std::map<int, Room>();
}

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	std::lock_guard<std::mutex> locker(room_lock);
	(*this->m_rooms)[id] = Room(user, data);//creating room yesss....
	id++;//increasing id
}

void RoomManager::deleteRoom(int ID)
{
	{
		std::lock_guard<std::mutex> locker(room_lock);
		m_rooms->erase(ID);//deleting room nooo....
	}
	
}

unsigned int RoomManager::getRoomState(int ID)
{
	{
		std::lock_guard<std::mutex> locker(room_lock);
		return ((*m_rooms)[ID].getData()).isActive;//getting if room is active
	}
	
}

std::vector<RoomData> RoomManager::getRooms()
{
	//getting vector of all rooms
	std::vector<RoomData> rooms;
	if(this->m_rooms->size() != 0)
	{
		{
			std::lock_guard<std::mutex> locker(room_lock);
			for (auto it = this->m_rooms->begin(); it != this->m_rooms->end(); it++)
			{
				rooms.push_back(it->second.getData());
			}
		}	
	}
	return rooms;
}

Room& RoomManager::getRoom(int ID)
{
	//getting a specific room by using ID
	{
		std::lock_guard<std::mutex> locker(room_lock);
		for (auto it = m_rooms->begin(); it != m_rooms->end(); it++)
		{
			if (it->first == ID)
			{
				return it->second;
			}
		}
	}
	
}


int RoomManager::getID()
{
	return id;
}
