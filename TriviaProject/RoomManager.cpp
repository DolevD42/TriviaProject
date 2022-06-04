#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser* user, RoomData data)
{
	std::pair<unsigned int, Room* > pair;
	pair.first = data.id;
	Room* room = new Room(data);
	pair.second = room;
	room->addUser(user);
	m_rooms.insert(pair);
}

void RoomManager::deleteRoom(int ID)
{
	auto it = m_rooms.find(ID);
	if (it == m_rooms.end())
	{
		return; //the room doesn't exist
	}
	m_rooms.erase(it);
	return;
}

unsigned int RoomManager::getRoomState(int ID)
{
	auto it = m_rooms.find(ID);
	if (it == m_rooms.end())
	{
		return -1; //room doesn't exist
	}
	return m_rooms[ID]->getRoomState();
}

std::vector<std::string> RoomManager::getRoomUsers(int ID)
{
	std::vector<std::string> vect;
	int specLoc = -1;
	for (int i = 0; i < getRooms().size(); i++)
	{
		if (getRooms()[i].id == ID)
		{
			specLoc = i;
		}
	}
	if (specLoc != -1)
	{
		vect = m_rooms[ID]->getAllUsers();
	}
	return vect;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> vect;
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->second->getRoomState() == ACTIVE_STATE)
		{
			vect.push_back(it->second->getRoomData());
		}
	}
	for (std::vector<RoomData>::const_iterator i = vect.begin(); i != vect.end(); ++i)
		std::cout << &i;
	return vect;
}

Room* RoomManager::getRoom(int ID)
{
	return m_rooms[ID];
}

bool RoomManager::checkIfRoomExist(int ID)
{
	bool returnValue = false;
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->first == ID)
		{
			returnValue = true;
		}
	}
	return returnValue;
}
