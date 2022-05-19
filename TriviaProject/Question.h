#pragma once
#include <string>
#include <vector>
class Question
{
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	int m_correct;

public:
	Question(std::string, std::vector<std::string>, int);
	~Question();
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	std::string getCorrectAnswer();
};
