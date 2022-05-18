#include "LoginManager.h"

LoginManager::LoginManager(): m_database(new SqliteDataBase())
{
	
}

void LoginManager::signup(std::string userName, std::string pass, std::string email)
{
	if (m_database->doesUserExist(userName))
	{
		return; //the user already exist
	}
	m_database->addNewUser(userName, pass, email);
	LoggedUser newUser = LoggedUser(userName);
	m_loggedUsers.push_back(newUser);
	return;
}

void LoginManager::login(std::string userName, std::string pass)
{
	if (!m_database->doesPasswordMatch(userName, pass))
	{
		return; // the password doesn't match the userName
	}
	LoggedUser newUser = LoggedUser(userName);
	m_loggedUsers.push_back(newUser);
	return;
}

void LoginManager::logout(std::string userName)
{
	int index = -1;
	for (int i = 0; i < m_loggedUsers.size(); i++)
	{
		if (m_loggedUsers[i].getUsername() == userName)
		{
			index = i;
		}
	}
	if (index != -1)
	{
		m_loggedUsers.erase(m_loggedUsers.begin()+index);
	}
	return;
}

