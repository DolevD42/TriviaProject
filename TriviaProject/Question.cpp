#include "Question.h"




Question::Question(std::string question, std::vector<std::string> possibleAnswers, int correct) : m_question(question), m_possibleAnswers(possibleAnswers), m_correct(correct)
{}

Question::~Question()
{}

std::string Question::getQuestion()
{
	return m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
	return m_possibleAnswers;
}

std::string Question::getCorrectAnswer()
{
	return m_possibleAnswers[m_correct];
}
