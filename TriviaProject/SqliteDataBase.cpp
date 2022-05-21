#include "SqliteDataBase.h"
#include <ctime>
#include <chrono>
#include <cstdlib>
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

int SqliteDataBase::getUserID(std::string username)
{
	std::string sqlStatement = "SELECT ID FROM USERS WHERE USERNAME = \"" + username + "\";";
	int id = 0;
	try
	{
		executeCommand(sqlStatement.c_str(), callbackGetIntegerValue, &id);
	}
	catch (std::exception er)
	{
		throw er;
	}

	return id;
}
//run an sql code
void SqliteDataBase::executeCommand(const char* statement)
{
	int res = 0;

	char** errMessage = nullptr;
	res = sqlite3_exec(this->_db, statement, nullptr, nullptr, errMessage);

	if (res != SQLITE_OK)
	{
		throw std::exception("Error in excecuting command on database");
	}
	
}
//insert result from sql statement to varible data
int SqliteDataBase::callbackGetIntegerValue(void* data, int argc, char** argv, char** azColName)
{
	*(int*)data = std::stoi(argv[0]);
	return 0;
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

float SqliteDataBase::getPlayerAverageAnswer(std::string id)
{
	std::string sqlStatement = "SELECT AVG(Answer_Time) FROM Players_Answers WHERE User_Id = " + std::to_string(this->getUserID(id)) + ";";
	float amount = 0;

	executeCommand(sqlStatement.c_str(), callbackGetIntegerValue, &amount);
	return amount;
}


