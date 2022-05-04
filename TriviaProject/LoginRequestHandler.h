#pragma once
#include "IRequestHandler.h"

#define LOGIN_CODE 1
#define VALID_RESPONSE 1
#define NON_VALIDRESPONSE 2

class LoginRequestHandler :
    public IRequestHandler
{
public:
    virtual bool isRequestRelevant(RequestInfo req);
    virtual RequestResult handleRequest(RequestInfo req);
};

