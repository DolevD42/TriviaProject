#include "LoginManager.h"

LoginManager::LoginManager(IDataBase* db): m_database(db)
{
	
}

LoginManager::~LoginManager()
{
}

int LoginManager::signup(std::string userName, std::string pass, std::string email)
{
	if (m_database->doesUserExist(userName))
	{
		return USER_ALREADY_EXIST; //the user already exist
	}
	m_database->addNewUser(userName, pass, email);
	LoggedUser newUser = LoggedUser(userName);
	m_loggedUsers.push_back(newUser);
	return REQUEST_VALID;
}

int LoginManager::login(std::string userName, std::string pass)
{
	int index = -1;
	if (!m_database->doesUserExist(userName))
	{
		return USER_DONT_EXIST;
	}
	if (!m_database->doesPasswordMatch(userName, pass))
	{
		return PASSWORD_DONT_MATCH; // the password doesn't match the userName
	}
	for (int i = 0; i < m_loggedUsers.size(); i++)
	{
		if (m_loggedUsers[i].getUsername() == userName)
		{
			index = i;
		}
	}
	if (index != -1)
	{
		return USER_ALREADY_LOGIN;
	}
	LoggedUser newUser = LoggedUser(userName);
	m_loggedUsers.push_back(newUser);
	return REQUEST_VALID;
}

int LoginManager::logout(std::string userName)
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
		return REQUEST_VALID;
	}
	return USER_DONT_EXIST;
}

