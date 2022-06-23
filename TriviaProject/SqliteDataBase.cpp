#include "SqliteDataBase.h"
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <sys/stat.h>
#include <algorithm>
#define RETRIVING_INFROMATION_ERROR "Error Accured While Retriving Information"
#define QUESTION_INSERT_PROBLEM "Question Insert Problem"

int exists(void* data, int argc, char** argv, char** azColName)
{
	*(bool*)data = true;
	return 0;
}
int avg(void* data, int argc, char** argv, char** azColName)
{
	*(float*)data = std::atof(argv[0]);
	return 0;
}

int sum(void* data, int argc, char** argv, char** azColName)
{
	*(int*)data = atoi(argv[0]);
	return 0;
}

int Rstring(void* data, int argc, char** argv, char** azColName)
{
	*(std::string*)data = argv[0];
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
sqlite3* SqliteDataBase::GetDb()
{
	if (_db == nullptr)
	{
		if (sqlite3_open("TriviaDB.sqlite", &_db) != SQLITE_OK)
		{
			_db = nullptr;
			throw std::exception("DB don't exist");
		}
	}
	return _db;
}

int SqliteDataBase::insertNewGame()
{
	time_t now = time(0);
	// convert now to string form
	char* dt = ctime(&now);
	std::string gameStatus = "0";//new game status equal zero
	std::string sqlStatement = "INSERT INTO games(status, start_time, end_time) VALUES ('" + gameStatus + "', '" + dt + "', 'NULL');";//not sure if it is working
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return -1;//something went wrong a new game did not inserted
	}
	else
	{
		this->_currGameId++;//tracking/counting the amount of games in the database
		return this->_currGameId;
	}
}

void SqliteDataBase::RemoveNewGame(int id)
{
	std::string sqlStatement = "DELETE FROM table_name WHERE condition game_id = '" + std::to_string(id) + "';";//not sure if it is working
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		throw(&errMessage);
	}

}


std::vector<std::string> SqliteDataBase::getAllUserName()
{
	std::vector<std::string> usernames;
	try
	{

		std::string sqlStatement = "SELECT username FROM users";
		sqlite3_stmt* stmt;
		if (sqlite3_prepare_v2(_db, sqlStatement.c_str(), strlen(sqlStatement.c_str()) + 1, &stmt, NULL) != SQLITE_OK)
			throw std::exception("error reading info");
		while (1)
		{
			int s;

			s = sqlite3_step(stmt);//get first row
			if (s == SQLITE_ROW)
			{
				std::string username = (char*)sqlite3_column_text(stmt, 0);
				usernames.push_back(username);

			}
			else if (s == SQLITE_DONE)
			{
				break;
			}
			else
			{
				sqlite3_finalize(stmt);
				throw std::exception("error reading info");
			}
		}
		return usernames;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return usernames;
	}
}

SqliteDataBase::SqliteDataBase()
{
	try
	{
		struct stat buffer;
		bool file_exist = stat(_filename.c_str(), &buffer) == 0;
		int res = sqlite3_open(this->_filename.c_str(), &this->_db);
		if (res != SQLITE_OK)
		{
			this->_db = nullptr;
			throw std::exception("Failed to open DB");
		}
		if (!file_exist)
		{
			std::string sqlStatement = "CREATE TABLE questions (question_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, question TEXT NOT NULL, correct_ans TEXT NOT NULL, ans2 TEXT NOT NULL, ans3 TEXT NOT NULL, ans4 TEXT NOT NULL);";
			char* errMessage = nullptr;
			res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Database Problem");
			sqlStatement = "CREATE TABLE games(game_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, status INTEGER NOT NULL, start_time DATETIME NOT NULL, end_time DATETIME);";
			res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Database Problem");
			sqlStatement = "CREATE TABLE users(username TEXT PRIMARY KEY NOT NULL, password TEXT NOT NULL, email TEXT);";
			res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Database Problem");
			sqlStatement = "CREATE TABLE statistics(username TEXT PRIMARY KEY NOT NULL, Wrong_Answers FLOAT NOT NULL, Correct_Answers INTEGER NOT NULL, answer_time FLOAT NOT NULL,Total_Answers INTEGER NOT NULL ,Total_Games INTEGER NOT NULL);";
			res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Database Problem");

			// Inserting the questions
			sqlStatement = "INSERT INTO questions (question, correct_ans, ans2, ans3, ans4) VALUES ('When did Albert Einstein win a noble prize?', '1921', '1922', '1928', '1926');";
			res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Question Insert Problem");

			//sqlStatement = "INSERT INTO questions (question, correct_ans, ans2, ans3, ans4) VALUES ('When was Albert Einstein Born?', '14.3.1879', '4.6.1878', '3.9.1885', '3.10.1877');";
			//res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			//if (res != SQLITE_OK)
			//	throw std::exception("Question Insert Problem");
			//
			//sqlStatement = "INSERT INTO questions (question, correct_ans, ans2, ans3, ans4) VALUES ('Where was Albert Einstein born?', 'Ulm', 'Hamburg', 'Dresden', 'Berlin');";
			//res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			//if (res != SQLITE_OK)
			//	throw std::exception("Question Insert Problem");
			//
			//sqlStatement = "INSERT INTO questions (question, correct_ans, ans2, ans3, ans4) VALUES ('When did Albert Einstein formulate his special theory of relativity', '1905', '1903', '1900', '1904');";
			//res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			//if (res != SQLITE_OK)
			//	throw std::exception("Question Insert Problem");
			//
			//sqlStatement = "INSERT INTO questions (question, correct_ans, ans2, ans3, ans4) VALUES ('How Many Hearts does an Occtupus have?', '1', '2', '3', '4');";
			//res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			//if (res != SQLITE_OK)
			//	throw std::exception("Question Insert Problem");
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
}

SqliteDataBase::~SqliteDataBase()
{
	sqlite3_close(this->_db);
	this->_db = nullptr;
}
void SqliteDataBase::InsertPlayerResults(std::string userName, int CorrectAnswerCount, int WrongAnswerCount, float averageAnswerTime, int AnswersCount)
{
	CorrectAnswerCount += getNumOfCorrectAnswers(userName);
	AnswersCount += getNumOfTotalAnswers(userName);
	WrongAnswerCount = AnswersCount - CorrectAnswerCount;
	averageAnswerTime += getPlayerAverageAnswerTime(userName);
	int gameCount = 1 + getNumOfPlayerGames(userName);
	std::string sqlMsg = "DELETE FROM statistics WHERE username ='"+userName+"'";
	if (sqlite3_exec(_db, sqlMsg.c_str(), nullptr, nullptr, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	std::string msgAfter = "INSERT INTO statistics (username, Wrong_Answers, Correct_Answers, answer_time, Total_Answers, Total_Games) VALUES('" + userName + "', '" + std::to_string(WrongAnswerCount) + "', '" + std::to_string(CorrectAnswerCount) + "', '" + std::to_string(averageAnswerTime) + "', '" + std::to_string(AnswersCount) + "', '" + std::to_string(gameCount) + "');";
	std::cout << msgAfter << std::endl;
	if (sqlite3_exec(_db, msgAfter.c_str(), nullptr, nullptr, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
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
	std::string msg2 = "INSERT INTO statistics (username, Wrong_Answers, Correct_Answers, answer_time, Total_Answers, Total_Games) VALUES('" + userName + "', '" + '0' + "', '" + '0' + "', '" + "0.0" + "', '" + '0' + "', '" + '0' + "');";
	if (sqlite3_exec(_db, msg2.c_str(), nullptr, nullptr, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	
}

std::list<Question*> SqliteDataBase::getQuestions()
{
	
	std::list<Question*> QuestionList;
	srand(time(NULL));
	try
	{
		int i = 1;
		std::string sqlStatement = "SELECT * FROM questions";
		sqlite3_stmt* stmt;
		if (sqlite3_prepare_v2(_db, sqlStatement.c_str(), strlen(sqlStatement.c_str()) + 1, &stmt, NULL) != SQLITE_OK)
			throw std::exception("error reading info");
		while (1)
		{
			int s;

			s = sqlite3_step(stmt);//get first row
			if (s == SQLITE_ROW)
			{
				std::string question = (char*)sqlite3_column_text(stmt, 1);
				std::string correctAns = (char*)sqlite3_column_text(stmt, 2);
				std::string ans2 = (char*)sqlite3_column_text(stmt, 3);
				std::string ans3 = (char*)sqlite3_column_text(stmt, 4);
				std::string ans4 = (char*)sqlite3_column_text(stmt, 5);
				Question* newQuestion = new Question(i, question, correctAns, ans2, ans3, ans4);//not sure if i sould free this memory later, also need to check if push_back shellow copy or not
				QuestionList.push_back(newQuestion);
				i++;
			}
			else if (s == SQLITE_DONE)
			{
				break;
			}
			else
			{
				sqlite3_finalize(stmt);
				throw std::exception(RETRIVING_INFROMATION_ERROR);
			}
		}

		sqlite3_finalize(stmt);
		return QuestionList;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return QuestionList;
	}
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string id)
{
	open();
	std::string sqlStatement = "SELECT AVG(answer_time) FROM statistics WHERE username = '" + id + "'; ";
	float amount = 0;
	if (sqlite3_exec(_db, sqlStatement.c_str(), avg, &amount, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	return amount;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string id)
{
	open();
	std::string sqlStatement = "SELECT SUM(Correct_Answers) FROM statistics WHERE username = '" + id + "';";
	int amount = 0;
	if (sqlite3_exec(_db, sqlStatement.c_str(), sum, &amount, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	return amount;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string id)
{
	open();
	std::string sqlStatement = "SELECT SUM(Total_Answers) FROM statistics WHERE username = '" + id + "';";
	int amount = 0;
	if (sqlite3_exec(_db, sqlStatement.c_str(), sum, &amount, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	return amount;
}

int SqliteDataBase::getNumOfPlayerGames(std::string id)
{
	open();
	std::string sqlStatement = "SELECT Total_Games FROM statistics WHERE username = '"+id+"';";
	int amount = 0;
	if (sqlite3_exec(_db, sqlStatement.c_str(), sum, &amount, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	return amount;
}


