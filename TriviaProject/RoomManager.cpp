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
	return vect;
}

Room* RoomManager::getRoom(int ID)
{
	if (m_rooms.find(ID) == m_rooms.end())
	{
		return NULL;
	}
	return m_rooms[ID];
}

Room* RoomManager::getLastRoomCreated()
{
	for (auto it = m_rooms.begin();it != m_rooms.end(); it++)
	{
		auto newIt = it;
		newIt++;
		if (newIt == m_rooms.end())
		{
			return it->second;
		}
	}
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

int RoomManager::getNumberOfRooms()
{
	return m_rooms.size();
}
