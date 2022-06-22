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
	std::map<unsigned int, std::string> map;
	for (int i = 0; i < 4; i++)
	{
		std::pair<unsigned int, std::string> pair;
		pair.first = i;
		pair.second = quest->getPossibleAnswers()[i];
	}
	res.answers = map;
	res.status = REQUEST_VALID;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this; 
	return returnReq;
	return RequestResult();
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
	return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(RequestInfo req)
{
	RequestResult returnReq;
	std::map<LoggedUser*, GameData> map;
	GetGameResultResponse res;
	std::vector<std::string> userName;
	std::vector<int> correctAnswerCount;
	std::vector<int> wrongAnswerCount;
	std::vector<float> averageAnswerTime;
	for (auto it = map.begin(); it != map.end(); it++)
	{
		userName.push_back(it->first->getUsername());
		correctAnswerCount.push_back(it->second.CorrectAnswerCount);
		wrongAnswerCount.push_back(it->second.WrongAnswerCount);
		averageAnswerTime.push_back(it->second.averageAnswerTime);
	}
	res.userName = userName;
	res.correctAnswerCount = correctAnswerCount;
	res.wrongAnswerCount = wrongAnswerCount;
	res.averageAnswerTime = averageAnswerTime;
	res.status = REQUEST_VALID;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this;
	return returnReq;
	return RequestResult();
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
	return RequestResult();
}
