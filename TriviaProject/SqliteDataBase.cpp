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
	open();
	std::string sqlStatement = "SELECT ID FROM USERS WHERE USERNAME = \"" + username + "\";";
	int id = 0;
	if (sqlite3_exec(_db, sqlStatement.c_str(), exists, &id, &_errMessage) != SQLITE_OK)
	{
		std::cout << "Falied to open DB" << std::endl;
	}
	return id;
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
			string sqlStatement = "CREATE TABLE t_questions (question_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, question TEXT NOT NULL, correct_ans TEXT NOT NULL, ans2 TEXT NOT NULL, ans3 TEXT NOT NULL, ans4 TEXT NOT NULL);";
			char* errMessage = nullptr;
			res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Database Problem");
			sqlStatement = "CREATE TABLE t_games(game_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, status INTEGER NOT NULL, start_time DATETIME NOT NULL, end_time DATETIME);";
			res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Database Problem");
			sqlStatement = "CREATE TABLE t_users(username TEXT PRIMARY KEY NOT NULL, password TEXT NOT NULL, email TEXT);";
			res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Database Problem");
			sqlStatement = "CREATE TABLE t_players_answers(game_id INTEGER NOT NULL, username TEXT NOT NULL, question_id INTEGER NOT NULL, player_answer TEXT NOT NULL, is_correct INTEGER NOT NULL, answer_time INTEGER NOT NULL, FOREIGN KEY(game_id) REFERENCES t_games(game_id), FOREIGN KEY(username) REFERENCES t_users(username), FOREIGN KEY(question_id) REFERENCES t_questions(question_id));";
			res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Database Problem");

			// Inserting the questions
			sqlStatement = "INSERT INTO t_questions (question, correct_ans, ans2, ans3, ans4) VALUES ('When did Albert Einstein win a noble prize?', '1921', '1922', '1928', '1926');";
			res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Question Insert Problem");

			sqlStatement = "INSERT INTO t_questions (question, correct_ans, ans2, ans3, ans4) VALUES ('When was Albert Einstein Born?', '14.3.1879', '4.6.1878', '3.9.1885', '3.10.1877');";
			res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Question Insert Problem");

			sqlStatement = "INSERT INTO t_questions (question, correct_ans, ans2, ans3, ans4) VALUES ('Where was Albert Einstein born?', 'Ulm', 'Hamburg', 'Dresden', 'Berlin');";
			res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Question Insert Problem");

			sqlStatement = "INSERT INTO t_questions (question, correct_ans, ans2, ans3, ans4) VALUES ('When did Albert Einstein formulate his special theory of relativity', '1905', '1903', '1900', '1904');";
			res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Question Insert Problem");

			sqlStatement = "INSERT INTO t_questions (question, correct_ans, ans2, ans3, ans4) VALUES ('How Many Hearts does an Occtupus have?', '1', '2', '3', '4');";
			res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw std::exception("Question Insert Problem");
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

std::list<Question*> SqliteDataBase::getQuestions(int id)
{
	
	std::list<Question*> QuestionList;
	srand(time(NULL));
	try
	{
		int i = 1;
		string sqlStatement = "SELECT * FROM t_questions";
		sqlite3_stmt* stmt;
		if (sqlite3_exec(_db, sqlStatement.c_str(), exists, &stmt, &_errMessage) != SQLITE_OK)
		{
			throw std::exception("DB don't exist");
		}
		while (1)
		{
			int s;

			s = sqlite3_step(stmt);//get first row
			if (s == SQLITE_ROW)
			{
				string question = (char*)sqlite3_column_text(stmt, 1);
				string correctAns = (char*)sqlite3_column_text(stmt, 2);
				string ans2 = (char*)sqlite3_column_text(stmt, 3);
				string ans3 = (char*)sqlite3_column_text(stmt, 4);
				string ans4 = (char*)sqlite3_column_text(stmt, 5);
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
		int vSize = QuestionList.size();
		while (vSize > id)//randomize to get random questions from data base
		{
			int randIndex = rand() % vSize;
			QuestionList.erase(QuestionList.begin() + randIndex);
			vSize--;
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
	std::string sqlStatement = "SELECT AVG(Answer_Time) FROM Players_Answers WHERE User_Id = " + std::to_string(this->getUserID(id)) + ";";
	float amount = 0;
	if (sqlite3_exec(_db, sqlStatement.c_str(), exists, &amount, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	return amount;
}

int SqliteDataBase::getNumOfCurrectAnswers(std::string id)
{
	open();
	std::string sqlStatement = "SELECT SUM(Correct_Answers) FROM Players_Answers WHERE User_Id = " + std::to_string(this->getUserID(id)) + ";";
	int amount = 0;
	if (sqlite3_exec(_db, sqlStatement.c_str(), exists, &amount, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	return amount;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string id)
{
	open();
	std::string sqlStatement = "SELECT SUM(Total_Answers) FROM Players_Answers WHERE User_Id = " + std::to_string(this->getUserID(id)) + ";";
	int amount = 0;
	if (sqlite3_exec(_db, sqlStatement.c_str(), exists, &amount, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	return amount;
}

int SqliteDataBase::getNumOfPlayerGames(std::string id)
{
	open();
	std::string sqlStatement = "SELECT SUM(Players);";
	int amount = 0;
	if (sqlite3_exec(_db, sqlStatement.c_str(), exists, &amount, &_errMessage) != SQLITE_OK)
	{
		throw std::exception("DB don't exist");
	}
	return amount;
}


