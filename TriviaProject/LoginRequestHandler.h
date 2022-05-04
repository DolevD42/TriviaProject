#pragma once
#include "IRequestHandler.h"
<<<<<<< Updated upstream
#define LOGIN_CODE 1
#define SIGNUP_RESPONSE 2

=======
<<<<<<< Updated upstream
=======
#define LOGIN_CODE 1
#define VALID_RESPONSE 1
#define NON_VALIDRESPONSE 2

>>>>>>> Stashed changes
>>>>>>> Stashed changes
class LoginRequestHandler :
    public IRequestHandler
{
public:
    virtual bool isRequestRelevant(RequestInfo req);
    virtual RequestResult handleRequest(RequestInfo req);
};

