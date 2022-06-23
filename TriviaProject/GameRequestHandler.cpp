#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(GameManager* gameManager, Game* game, RequestHandlerFactory* handlerFactory, LoggedUser* user, SOCKET socket)
{
	m_handlerFactory = handlerFactory;
	m_gameManager = gameManager;
	m_game = game;
	m_user = user;
	m_socket = socket;
}

GameRequestHandler::~GameRequestHandler()
{

}

bool GameRequestHandler::isRequestRelevant(RequestInfo req)
{
	if (req.id == SUBMIT_ANSWER_CODE || req.id == GET_QUESTION_CODE || req.id == LEAVE_GAME_CODE || req.id == GET_GAME_CODE)
	{
		return true;
	}
	return false;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo req)
{
	RequestResult returnReq;
	if (!isRequestRelevant(req))
	{

		returnReq.newHandler = this;
		ErrorResponse res;
		res.message = "INVALID CODE";
		returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
		return returnReq;
	}
	switch (req.id) {
	case SUBMIT_ANSWER_CODE:
		returnReq = submitAnswer(req);
		break;
	case GET_QUESTION_CODE:
		returnReq = getQuestion(req);
		break;
	case LEAVE_GAME_CODE:
		returnReq = leaveGame(req);
		break;
	case GET_GAME_CODE:
		returnReq = getGameResults(req);
		break;
	}
	return returnReq;
}

RequestResult GameRequestHandler::getQuestion(RequestInfo req)
{
	RequestResult returnReq;
	Question* quest;
	quest = m_game->getQuestionForUser(m_user);
	

	GetQuestionResponse res;
	res.Question = quest->getQuestion();
	std::vector<std::string> vectAnswers;
	std::vector<int> vectID;
	
	for (int i = 0; i < 4; i++)
	{
		vectID.push_back(i);
		vectAnswers.push_back(quest->getPossibleAnswers()[i]);
	}
	res.answers = vectAnswers;
	res.IdPerQuestion = vectID;
	res.status = REQUEST_VALID;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this; 
	return returnReq;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo req)
{
	RequestResult returnReq;
	SubmitAnswerRequest specReq = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(req.buffer);
	
	SubmitAnswerResponse res;
	res.CorrectAnswerId = m_game->submitAnswer(m_user, specReq.answerId, specReq.timePerAns);
	res.status = REQUEST_VALID;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this;
	return returnReq;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo req)
{
	RequestResult returnReq;
	std::map<LoggedUser*, GameData> map;
	GetGameResultResponse res;
	int funcCode = REQUEST_VALID;
	std::vector<std::string> userName;
	std::vector<int> correctAnswerCount;
	std::vector<int> wrongAnswerCount;
	std::vector<float> averageAnswerTime;
	map = m_game->getData();
	m_game->changeUserStatus(m_user, false);
	for (auto it = map.begin(); it != map.end(); it++)
	{
		if (it->second.playing == true)
		{
			funcCode = GAME_STILL_GOING_ON;
		}
		userName.push_back(it->first->getUsername());
		correctAnswerCount.push_back(it->second.CorrectAnswerCount);
		wrongAnswerCount.push_back(it->second.WrongAnswerCount);
		averageAnswerTime.push_back(it->second.averageAnswerTime);
		
	}
	if (funcCode == REQUEST_VALID)
	{
		res.userName = userName;
		res.correctAnswerCount = correctAnswerCount;
		res.wrongAnswerCount = wrongAnswerCount;
		res.averageAnswerTime = averageAnswerTime;
		res.status = funcCode;
	}
	else
	{
		res.userName = std::vector<std::string>();
		res.correctAnswerCount = std::vector<int>();
		res.wrongAnswerCount = std::vector<int>();
		res.averageAnswerTime = std::vector<float>();
		res.status = funcCode;
	}
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this;
	return returnReq;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo req)
{
	RequestResult returnReq;
	m_game->removePlayer(m_user);

	LeaveGameResponse res;
	res.status = REQUEST_VALID;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = m_handlerFactory->createMenuRequestHandler(m_socket, m_user);
	return returnReq;
}
