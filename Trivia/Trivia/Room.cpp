#include "Room.h"
//C'tor
Room::Room(LoggedUser user, RoomData data)
{
	m_users = new std::vector<LoggedUser>();
	this->m_users->push_back(user);
	m_metadata = data;
}

void Room::addUser(LoggedUser user)
{
	this->m_users->push_back(user);//adding user to room
}

void Room::removeUser(LoggedUser user)
{

	for (auto it = this->m_users->begin(); it != this->m_users->end(); it++)//going trough all users and finding the one that want's to leave and kicking him out (because fuck him)
	{
		if (it->getUserName() == user.getUserName())
		{
			this->m_users->erase(it);
			return;
		}
	}
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> users;
	for (auto it = this->m_users->begin(); it != this->m_users->end(); it++)//getting strings of all users name inside of a vector
	{
		users.push_back(it->getUserName());
	}
	return users;
}

void Room::activate()
{
	m_metadata.isActive = GAMEBEGUN;
}

void Room::close()
{
	m_metadata.isActive = CLOSED;
}

RoomData Room::getData()
{
	return m_metadata;
}
