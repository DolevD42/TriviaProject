#include "RoomMemberRequestHandler.h"
RoomMemberRequestHandler::RoomMemberRequestHandler(RoomManager* roomManager, Room* room, RequestHandlerFactory* handlerFactory, LoggedUser* user, SOCKET socket)
{
	m_handlerFactory = handlerFactory;
	m_roomManager = roomManager;
	m_room = room;
	m_user = user;
	m_socket = socket;
}
RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo req)
{
	if (req.id == LEAVE_ROOM_CODE || req.id == GET_ROOM_STATE_CODE)
	{
		return true;
	}
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo req)
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
	case LEAVE_ROOM_CODE:
		returnReq = leaveRoom(req);
		break;
	case GET_ROOM_STATE_CODE:
		returnReq = getRoomState(req);
		break;
	}
	return returnReq;
}


RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo req)
{
	RequestResult returnReq;
	int wantedID = -1;
	int wantedPlace = -1;
	SOCKET socket;
	int funcCode = ROOM_DONT_EXIST;
	int i = 0;
	for (i = 0; i < m_roomManager->getNumberOfRooms(); i++)
	{
		if (m_roomManager->getRoom(i) != NULL)
		{
			for (int j = 0; j < m_roomManager->getRoom(i)->getAllUsers().size(); j++)
			{
				if (m_roomManager->getRoom(i)->getAllUsers()[j] == m_user->getUsername())
				{
					wantedID = i;
					wantedPlace = j;
					funcCode = REQUEST_VALID;
				}
			}
		}
	}
	if (funcCode == REQUEST_VALID)
	{
		m_roomManager->getRoom(wantedID)->removeUser(m_roomManager->getRoom(wantedID)->getLoggedUser(wantedPlace));
		returnReq.newHandler = m_handlerFactory->createMenuRequestHandler(m_socket, m_user);
	}
	else
	{
		returnReq.newHandler = m_handlerFactory->createMenuRequestHandler(m_socket, m_user);
	}
	LeaveRoomResponse res;
	res.status = funcCode;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	return returnReq;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo req)
{
	RequestResult returnReq;
	int wantedID = -1;
	SOCKET socket;
	int funcCode = ROOM_DONT_EXIST;
	int i = 0;
	for (i = 0; i < m_roomManager->getNumberOfRooms(); i++)
	{
		if (m_roomManager->getRoom(i) != NULL)
		{
			for (int j = 0; j < m_roomManager->getRoom(i)->getAllUsers().size(); j++)
			{
				if (m_roomManager->getRoom(i)->getAllUsers()[j] == m_user->getUsername())
				{
					wantedID = i;
					funcCode = REQUEST_VALID;
				}
			}
		}
	}

	GetRoomStateResponse res;
	if (wantedID != -1)
	{
		res.answerTimeOut = m_roomManager->getRoom(wantedID)->getRoomData().timePerQuestion;
		res.players = m_roomManager->getRoom(wantedID)->getAllUsers();
		res.questionCount = m_roomManager->getRoom(wantedID)->getRoomData().numOfQuestionInGame;
		res.status = m_roomManager->getRoom(wantedID)->getRoomData().isActive;
		if (m_roomManager->getRoom(wantedID)->getRoomData().isActive == GAME_STARTED_STATE)
		{
			res.hasGameBegun = true;
		}
		else
		{
			res.hasGameBegun = false;
		}
	}
	else
	{
		res.answerTimeOut = 0;
		res.hasGameBegun = false;
		std::vector<std::string> vect;
		res.players = vect;
		res.questionCount = 0;
		res.status = NON_ACTIVE_STATE;
	}

	res.status = funcCode;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = this; //Here we will put the gameHandler
	return returnReq;
}