#pragma once

#include <string>
#include <stdio.h>
#include <vector>
#include "SqliteDataBase.h"
#include "LoggedUser.h"


class LoginManager
{
public:
	LoginManager(IDataBase* db);
	~LoginManager();
	int signup(std::string userName, std::string pass, std::string email);
	int login(std::string userName, std::string pass);
	int logout(std::string userName);
private:
	IDataBase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};

