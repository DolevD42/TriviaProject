#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "StatisticsManager.h"

class RequestHandlerFactory;
class MenuRequestHandler :
    public IRequestHandler
{
public:
    MenuRequestHandler(RoomManager* roomManager, StatisticsManager* staticsManager ,RequestHandlerFactory* handlerFactory);
    ~MenuRequestHandler();
    virtual bool isRequestRelevant(RequestInfo req);
    virtual RequestResult handleRequest(RequestInfo req);
    void setUser(LoggedUser* user);
private:
    RequestResult signout(RequestInfo req);
    RequestResult getRooms(RequestInfo req);
    RequestResult getPlayersInRoom(RequestInfo req);
    RequestResult getPersonalStats(RequestInfo req);
    RequestResult getHighScore(RequestInfo req);
    RequestResult joinRoom(RequestInfo req);
    RequestResult createRoom(RequestInfo req);

    LoggedUser* m_user;
    RoomManager* m_roomManager;
    StatisticsManager* m_statisticsManager;
    RequestHandlerFactory* m_handlerFactory;
};

