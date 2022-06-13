#pragma once
#include <string>
#include <vector>
#include "Helper.h"

class Question
{
public:
	Question(int id, std::string question, std::string correctAnswer, std::string answer2, std::string answer3, std::string answer4);
	std::string getQuestion();
	int getCorrectAnswerIndex();
	std::vector<std::string> getPossibleAnswers();
	int getId();
	~Question();
	
private:
	std::string _question;
	std::string _answers[4];
	int _correctAnswerIndex;
	int _id;
};
