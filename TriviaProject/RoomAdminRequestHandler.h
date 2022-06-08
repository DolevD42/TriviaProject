#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;

class RoomAdminRequestHandler :
    public IRequestHandler
{
public:
    RoomAdminRequestHandler(RoomManager* roomManager, Room* room, RequestHandlerFactory* handlerFactory,LoggedUser* user, SOCKET socket);
    ~RoomAdminRequestHandler();
    virtual bool isRequestRelevant(RequestInfo req);
    virtual RequestResult handleRequest(RequestInfo req);
private:
    RequestResult closeRoom(RequestInfo req);
    RequestResult startGame(RequestInfo req);
    RequestResult getRoomState(RequestInfo req);

    LoggedUser* m_user;
    RoomManager* m_roomManager;
    Room* m_room;
    RequestHandlerFactory* m_handlerFactory;
};

