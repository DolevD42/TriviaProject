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
    if (!isRequestRelevant(req))
    {
        returnReq.newHandler = this;
        std::vector<char> vec; //add error response
        returnReq.response = vec;
        return returnReq;
    }
    if (req.id == LOGIN_CODE)
    {
        LoginResponse res;
        LoginRequest logReq = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);

        //Here we will handle the request and check if everything is valid


        res.status = VALID_RESPONSE;
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    if (req.id == SIGNUP_RESPONSE)
    {
        SignupResponse res;
        SignupRequest signReq = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);


        //Here we will handle the request and check if everything is valid


        res.status = VALID_RESPONSE;
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    IRequestHandler* log = new LoginRequestHandler(); //we will change it later to another handler
    returnReq.newHandler = log;
    return returnReq;
}
