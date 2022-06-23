#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;

class RoomMemberRequestHandler :
    public IRequestHandler
{
public:
    RoomMemberRequestHandler(RoomManager* roomManager, Room* room, RequestHandlerFactory* handlerFactory, LoggedUser* user, SOCKET socket);
    ~RoomMemberRequestHandler();
    virtual bool isRequestRelevant(RequestInfo req);
    virtual RequestResult handleRequest(RequestInfo req);
private:
    RequestResult leaveRoom(RequestInfo req);
    RequestResult getRoomState(RequestInfo req);
    RequestResult startGame(RequestInfo req);
    LoggedUser* m_user;
    RoomManager* m_roomManager;
    Room* m_room;
    RequestHandlerFactory* m_handlerFactory;
};

