#include "Room.h"



Room::Room(LoggedUser user, RoomData data)
{
	this->m_users.push_back(user);
	m_metadata = data;
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	for (auto it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		if (it->getUserName() == user.getUserName())
		{
			this->m_users.erase(it);
		}
	}
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> users;
	for (auto it = this->m_users.begin(); it != this->m_users.end(); it++)
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
