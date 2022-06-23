#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class GameRequestHandler :
    public IRequestHandler
{
public:
    GameRequestHandler(GameManager* gameManager, Game* game, RequestHandlerFactory* handlerFactory, LoggedUser* user, SOCKET socket);
    ~GameRequestHandler();
    virtual bool isRequestRelevant(RequestInfo req);
    virtual RequestResult handleRequest(RequestInfo req);
private:
    RequestResult getQuestion(RequestInfo req);
    RequestResult submitAnswer(RequestInfo req);
    RequestResult getGameResults(RequestInfo req);
    RequestResult leaveGame(RequestInfo req);

    LoggedUser* m_user;
    GameManager* m_gameManager;
    Game* m_game;
    RequestHandlerFactory* m_handlerFactory;
};

