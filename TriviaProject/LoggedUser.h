#pragma once
#include <string>
#include <stdio.h>

class LoggedUser
{
public:
	LoggedUser(std::string userName);
	std::string getUsername();
private:
	std::string m_username;
};

