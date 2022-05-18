#pragma once

#include <string>
#include <stdio.h>
#include <vector>
#include "SqliteDataBase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager();
	void signup(std::string userName, std::string pass, std::string email);
	void login(std::string userName, std::string pass);
	void logout(std::string userName);
private:
	IDataBase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};

