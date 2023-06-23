#include "RoomManager.h"

int RoomManager::id = 1;
std::mutex RoomManager::room_lock;
RoomManager::RoomManager()
{
	m_rooms = new std::map<int, Room>();
}
RoomManager::~RoomManager()
{
	delete m_rooms;
}
void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	std::lock_guard<std::mutex> locker(room_lock);
	(*this->m_rooms)[id] = Room(user, data);
	id++;
}

void RoomManager::deleteRoom(int ID)
{
	{
		std::lock_guard<std::mutex> locker(room_lock);
		m_rooms->erase(ID);
	}
	
}

unsigned int RoomManager::getRoomState(int ID)
{
	{
		std::lock_guard<std::mutex> locker(room_lock);
		return ((*m_rooms)[ID].getData()).isActive;
	}
	
}

std::vector<RoomData> RoomManager::getRooms()
{
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
