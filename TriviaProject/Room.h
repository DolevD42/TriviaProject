#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "LoggedUser.h"
#include "Helper.h"

typedef struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;


class Room
{
public:
	Room(RoomData data);
	int addUser(LoggedUser* user);
	int removeUser(LoggedUser* user);
	std::vector<std::string> getAllUsers();
	std::vector<SOCKET> getAllSocket();
	LoggedUser* getLoggedUser(int place);
	std::vector<LoggedUser*> getAllLoggedUser();
	unsigned int getRoomState();
	RoomData getRoomData();
private:
	RoomData m_metadata;
	std::vector<LoggedUser*> m_users;
};

