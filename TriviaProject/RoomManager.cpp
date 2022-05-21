#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	std::pair<unsigned int, Room* > pair;
	pair.first = data.id;
	Room* room = new Room(data);
	room->addUser(user);

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
