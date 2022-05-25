#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "LoginManager.h"

class RequestHandlerFactory;

class LoginRequestHandler :
    public IRequestHandler
{
public:
    LoginRequestHandler(LoginManager* loginManager, RequestHandlerFactory* handlerFactory);
    ~LoginRequestHandler();
    virtual bool isRequestRelevant(RequestInfo req);
    virtual RequestResult handleRequest(RequestInfo req);
private:
    LoginManager* m_loginManager;
    RequestHandlerFactory* m_handlerFactory;
    RequestResult login(const RequestInfo& rqst);
    RequestResult signup(const RequestInfo& rqst);
};

