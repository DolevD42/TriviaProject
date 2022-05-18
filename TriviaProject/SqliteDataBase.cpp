#include "SqliteDataBase.h"
int exists(void* data, int argc, char** argv, char** azColName)
{
	*(bool*)data = true;
	return 0;
}

bool SqliteDataBase::open()
{
	if (_db == nullptr)
	{
		if (sqlite3_open("TriviaDB.sqlite", &_db) != SQLITE_OK)
		{
			_db = nullptr;
			throw std::exception("DB don't exist");
		}
		return false;
	}
}

bool SqliteDataBase::doesUserExist(std::string userName)
{
	open();
	bool retunValue = false;
	std::string msg = "select * from users where username == '" + userName + "';";
	if (sqlite3_exec(_db, msg.c_str(), exists, &retunValue, &_errMessage) != SQLITE_OK)
	{
		std::cout << "Falied to open DB" << std::endl;
	}
	return retunValue;

}

bool SqliteDataBase::doesPasswordMatch(std::string userName, std::string pass)
{
	open();
	bool flag = false;
	std::string msg = "select * from users where username == '" + userName + "' and password = '" + pass + "';";
	if (sqlite3_exec(_db, msg.c_str(), exists, &flag, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}

	return flag;
}

void SqliteDataBase::addNewUser(std::string userName, std::string pass, std::string email)
{
	open();
	std::string msg = "INSERT INTO users (username, password, email) VALUES('" + userName + "', '" + pass + "', '" + email + "');";
	if (sqlite3_exec(_db, msg.c_str(), nullptr, nullptr, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
}


