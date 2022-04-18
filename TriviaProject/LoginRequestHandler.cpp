#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo req)
{
    if (req.id == LOGIN_CODE || req.id == SIGNUP_RESPONSE)
    {
        return true;
    }
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo req)
{
    RequestResult returnReq;
    if (req.id == LOGIN_CODE)
    {
        LoginResponse res;
        res.status = (int)req.buffer.get();
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    if (req.id == SIGNUP_RESPONSE)
    {
        SignupResponse res;
        res.status = (int)req.buffer.get();
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    LoginRequestHandler* log = new LoginRequestHandler();
    //returnReq.newHandler = log;
    return returnReq;
}
