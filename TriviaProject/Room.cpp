#include "Room.h"

Room::Room(RoomData data): m_metadata(data)
{
}

unsigned int Room::getRoomState()
{
	return m_metadata.isActive;
}

RoomData Room::getRoomData()
{
	return m_metadata;
}
