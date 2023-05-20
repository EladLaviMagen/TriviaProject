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
	return 0;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	return rooms;
}

Room& RoomManager::getRoom(int ID)
{
	return m_rooms[ID];
}
