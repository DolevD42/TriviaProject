#pragma once

#include <string>
#include <stdio.h>
#include <vector>
#include "SqliteDataBase.h"
#include "LoggedUser.h"

#define PASSWORD_DONT_MATCH 41
#define REQUEST_VALID 42
#define USER_ALREADY_EXIST 43
#define USER_DONT_EXIST 44
#define USER_ALREADY_LOGIN 45


class LoginManager
{
public:
	LoginManager();
	LoginManager(IDataBase* db);
	int signup(std::string userName, std::string pass, std::string email);
	int login(std::string userName, std::string pass);
	int logout(std::string userName);
private:
	IDataBase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};

