#include "Room.h"

Room::Room(RoomData data): m_metadata(data)
{
}

int Room::addUser(LoggedUser* user)
{
	if (m_users.size() == m_metadata.maxPlayers)
	{
		return ROOM_MAX_OUT; //can't get another user to the list
	}
	int index = -1;
	for (int i = 0; i < m_users.size(); i++)
	{
		if (m_users[i]->getUsername() == user->getUsername())
		{
			index = i;
		}
	}
	if (index != -1)
	{
		return USER_ALREADY_EXIST; //the user already exist
	}
	m_users.push_back(user);
	return REQUEST_VALID;

}

int Room::removeUser(LoggedUser* user)
{
	int index = -1;
	for (int i = 0; i < m_users.size(); i++)
	{
		if (m_users[i]->getUsername() == user->getUsername())
		{
			index = i;
		}
	}
	if (index != -1)
	{
		m_users.erase(m_users.begin() + index);
		return REQUEST_VALID;
	}
	return USER_DONT_EXIST; //the user don't exist
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> vect;
	for (int i = 0; i < m_users.size(); i++)
	{
		vect.push_back(m_users[i]->getUsername());
	}
	return vect;
}

unsigned int Room::getRoomState()
{
	return m_metadata.isActive;
}

RoomData Room::getRoomData()
{
	return m_metadata;
}
