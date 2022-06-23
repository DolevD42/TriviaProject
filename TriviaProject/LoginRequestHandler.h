#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <Windows.h>
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "LoginManager.h"

class RequestHandlerFactory;

class LoginRequestHandler :
    public IRequestHandler
{
public:
    LoginRequestHandler(LoginManager* loginManager, RequestHandlerFactory* handlerFactory, SOCKET socket);
    ~LoginRequestHandler();
    virtual bool isRequestRelevant(RequestInfo req);
    virtual RequestResult handleRequest(RequestInfo req);
private:
    LoginManager* m_loginManager;
    
    RequestHandlerFactory* m_handlerFactory;
    RequestResult login(const RequestInfo& rqst);
    RequestResult signup(const RequestInfo& rqst);
};

