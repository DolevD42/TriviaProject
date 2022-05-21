#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "LoggedUser.h"

#define ACTIVE_STATE 42

typedef struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int munOfQuestionInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;


class Room
{
public:
	Room(RoomData data);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();

	unsigned int getRoomState();
	RoomData getRoomData();
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

