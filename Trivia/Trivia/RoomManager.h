#pragma once
#include <map>
#include "LoggedUser.h"
#include "Room.h"
class RoomManager
{
public:
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
private:
	static int id;
	std::map<int, Room> m_rooms;
};

