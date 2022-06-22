#include "RoomAdminRequestHandler.h"
RoomAdminRequestHandler::RoomAdminRequestHandler(RoomManager* roomManager, Room* room, RequestHandlerFactory* handlerFactory, LoggedUser* user, SOCKET socket)
{
	m_handlerFactory = handlerFactory;
	m_roomManager = roomManager;
	m_room = room;
	m_user = user;
	m_socket = socket;
}
RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo req)
{
	if (req.id == CLOSE_ROOM_CODE || req.id == START_GAME_CODE || req.id == GET_ROOM_STATE_CODE)
	{
		return true;
	}
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo req)
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
	case CLOSE_ROOM_CODE:
		returnReq = closeRoom(req);
		break;
	case START_GAME_CODE:
		returnReq = startGame(req);
		break;
	case GET_ROOM_STATE_CODE:
		returnReq = getRoomState(req);
		break;
	}
	return returnReq;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo req)
{
	RequestResult returnReq;
	int wantedID = -1;
	SOCKET socket;
	int funcCode = ROOM_DONT_EXIST;
	int i = 0;
	for (i = 0; i < m_roomManager->getNumberOfRooms(); i++)
	{
		if(m_roomManager->getRoom(i)!=NULL)
		{ 
			if (m_roomManager->getRoom(i)->getAllUsers()[0] == m_user->getUsername())
			{
				wantedID = i;
			}
		}
	}
	if (wantedID != -1)
	{
		for (i = 1; i < m_roomManager->getRoom(wantedID)->getAllSocket().size(); i++)
		{
			socket = m_roomManager->getRoom(wantedID)->getAllSocket()[i];
			Helper::sendData(socket, LEAVE_ROOM_CLIENT_MSG);
		}
		m_roomManager->getRoom(wantedID)->removeUser(m_roomManager->getRoom(wantedID)->getLoggedUser(0));
		m_roomManager->deleteRoom(wantedID);
		funcCode = REQUEST_VALID;
	}
	
	CloseRoomResponse res;
	res.status = funcCode;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = m_handlerFactory->createMenuRequestHandler(m_socket, m_user);
	return returnReq;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo req)
{
	RequestResult returnReq;
	int wantedID = -1;
	SOCKET socket;
	int funcCode = ROOM_DONT_EXIST;
	int i = 0;
	for (i = 1; i < m_roomManager->getNumberOfRooms(); i++)
	{
		if (m_roomManager->getRoom(i) != NULL)
		{
			if (m_roomManager->getRoom(i)->getAllUsers()[0] == m_user->getUsername()) //check if the admin name is the same as the name who sent
			{
				wantedID = i;
			}
		}
	}
	if (wantedID != -1)
	{
		for (i = 0; i < m_roomManager->getRoom(wantedID)->getAllSocket().size(); i++)
		{
			socket = m_roomManager->getRoom(wantedID)->getAllSocket()[i];
			Helper::sendData(socket, START_GAME_CLIENT_MSG);
		}
		
		funcCode = REQUEST_VALID;
	}

	StartGameResponse res;
	res.status = funcCode;
	returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
	returnReq.newHandler = m_handlerFactory->createGameRequestHandler(m_socket, m_user, m_room); 
	return returnReq;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo req)
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
			if (m_roomManager->getRoom(i)->getAllUsers()[0] == m_user->getUsername()) //check if the admin name is the same as the name who sent
			{
				wantedID = i;
				funcCode = REQUEST_VALID;
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