#include "Question.h"

Question::Question(int id, std::string question, std::string correctAnswer, std::string answer2, std::string answer3, std::string answer4)
{
	int correctAnswerIndex, index2 = -1, index3 = -1, index4 = -1;

	_id = id;
	_question = std::string(question);

	//Correct answer index.
	correctAnswerIndex = rand() % 4;
	_answers[correctAnswerIndex] = std::string(correctAnswer);
	_correctAnswerIndex = correctAnswerIndex;

	//Second answer index
	while (index2 == correctAnswerIndex || index2 == -1) { index2 = rand() % 4; }
	_answers[index2] = std::string(answer2);

	//Third answer index
	while (index3 == correctAnswerIndex || index3 == index2 || index3 == -1) { index3 = rand() % 4; }
	_answers[index3] = std::string(answer3);

	//Fourth answer index
	while (index4 == correctAnswerIndex || index4 == index3 || index4 == index2 || index4 == -1) { index4 = rand() % 4; }
	_answers[index4] = std::string(answer4);
}

std::string Question::getQuestion()
{
	return std::string(_question);
}

std::string* Question::getAnswers()
{
	return new std::string[4]{ _answers[0], _answers[1], _answers[2], _answers[3] };
}

int Question::getCorrectAnswerIndex()
{
	return _correctAnswerIndex;
}

int Question::getId()
{
	return _id;
}

Question::~Question()
{
	delete _answers;
}
