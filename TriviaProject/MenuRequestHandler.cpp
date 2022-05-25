#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RoomManager* roomManager, StatisticsManager* staticsManager, RequestHandlerFactory* handlerFactory)
{
	m_handlerFactory = handlerFactory;
	m_roomManager = roomManager;
	m_statisticsManager = staticsManager;
	m_user = NULL;
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo req)
{
	if (req.id <= CREATE_ROOM_CODE && req.id >= LOGOUT_CODE)
	{
		return true;
	}
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo req)
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
	case LOGOUT_CODE:
		returnReq = signout(req);
		break;
	case GET_ROOMS_CODE:
		returnReq = getRooms(req);
		break;
	case GET_PLAYERS_CODE:
		returnReq = getPlayersInRoom(req);
		break;
	case GET_HIGH_CODE:
		returnReq = getHighScore(req);
		break;
	case GET_PERSONAL_CODE:
		returnReq = getPersonalStats(req);
		break;
	case JOIN_ROOM_CODE:
		returnReq = joinRoom(req);
		break;
	case CREATE_ROOM_CODE:
		returnReq = createRoom(req);
		break;
	}
	return returnReq;
}

void MenuRequestHandler::setUser(LoggedUser* user)
{
	m_user = user;
}

RequestResult MenuRequestHandler::signout(RequestInfo)
{
	int funcCode;
	RequestResult returnReq;
	funcCode = m_handlerFactory->getLoginManager()->logout(m_user->getUsername());
	LogoutResponse res;
	res.status = funcCode;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = m_handlerFactory->createLoginRequestHandler();
	return returnReq;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo)
{
	RequestResult returnReq;
	
	GetRoomsResponse res;
	res.status = REQUEST_VALID;
	res.rooms = m_roomManager->getRooms();
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this;
	return returnReq;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo req)
{
	RequestResult returnReq;
	GetPlayersInRoomRequest specReq = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(req.buffer);
	
	GetPlayersInRoomResponse res;
	res.players = m_roomManager->getRoomUsers(specReq.roomId);
	if (res.players.size() == 0)
	{
		ErrorResponse errRes;
		errRes.message = "There wasn't Room like this";
		returnReq.response = JsonResponsePacketSerializer::serializeResponse(errRes);
	}
	else
	{
		returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	}
	returnReq.newHandler = this;
	return returnReq;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo req)
{
	std::vector<std::string> vect;
	RequestResult returnReq;
	vect = m_statisticsManager->getUserStatistics(m_user->getUsername());
	GetPersonalStatsResponse res;
	res.status = REQUEST_VALID;
	res.statistics = vect;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this;
	return returnReq;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo req)
{
	std::vector<std::string> vect;
	RequestResult returnReq;
	vect = m_statisticsManager->getHighScore();
	GetHighScoreResponse res;
	res.status = REQUEST_VALID;
	res.statistics = vect;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this;
	return returnReq;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo req)
{
	RequestResult returnReq;
	JoinRoomRequest specReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(req.buffer);
	int funcCode = ROOM_DONT_EXIST;
	JoinRoomResponse res;
	if (m_roomManager->checkIfRoomExist(specReq.roomId))
	{
		funcCode = m_roomManager->getRoom(specReq.roomId)->addUser(m_user);
	}
	res.status = funcCode;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this;
	return returnReq;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo req)
{
	RequestResult returnReq;
	int funcCode = 0;
	RoomData data;
	CreateRoomRequest specReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(req.buffer);
	if (specReq.maxUsers <= 0 || specReq.questionCount <= 0 || specReq.answerTimeout <= 0)
	{
		funcCode =  WRONG_PARAMETERS;
	}
	else
	{
		funcCode = REQUEST_VALID;
		if (m_roomManager->checkIfRoomExist(0))
		{
			data.id = m_roomManager->getRooms()[m_roomManager->getRooms().size() - 1].id + 1;
		}
		else
		{
			data.id = 0;
		}
		data.isActive = NON_ACTIVE_STATE;
		data.maxPlayers = specReq.maxUsers;
		data.numOfQuestionInGame = specReq.questionCount;
		data.name = specReq.roomName;
		data.timePerQuestion = specReq.answerTimeout;
		m_roomManager->createRoom(m_user, data);
	}
	CreateRoomResponse res;
	res.status = funcCode;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this;
	return returnReq;
}
