#pragma once
#include <map>
#include "LoggedUser.h"
#include "Room.h"
#include "RoomNotExist.h"
#include <mutex>

class LoggedUser;
class Room;

class RoomManager
{
public:
	RoomManager();
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
	int assignID();
	int getID();
private:
	static std::mutex room_lock;
	static int id;
	std::map<int, Room> m_rooms;
};

