#pragma once
#include "SqliteDataBase.h"
#include "IDataBase.h"
#include "LoggedUser.h"
#include <map>
class GameManager
{
public:

	Question CurrentQuestion();
	unsigned int CorrectAnswerCount();
	unsigned int WrongAnswerCount();
	float AverangeAnswerTime();
};