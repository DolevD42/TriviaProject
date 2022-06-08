#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Room.h"



class RoomManager
{
public:
	void createRoom(LoggedUser* user, RoomData data);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<std::string> getRoomUsers(int ID);
	std::vector<RoomData> getRooms();
	Room* getRoom(int ID);
	Room* getLastRoomCreated();
	bool checkIfRoomExist(int ID);
	int getNumberOfRooms();
	
private:
	std::map<unsigned int, Room*> m_rooms;
};

