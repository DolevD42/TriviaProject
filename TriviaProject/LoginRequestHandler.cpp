#include "LoginRequestHandler.h"
<<<<<<< Updated upstream
=======
<<<<<<< Updated upstream
=======
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
    if (req.id == LOGIN_CODE)
    {
        LoginResponse res;
        res.status = (int)req.buffer.get();
=======
    if (!isRequestRelevant(req))
    {
        returnReq.newHandler = this;
        std::vector<char> vec;
        returnReq.response = vec;
        return returnReq;
    }
    if (req.id == LOGIN_CODE)
    {
        LoginResponse res; 
        LoginRequest logReq = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
        
        //Here we will handle the request and check if everything is valid

        
        res.status = VALID_RESPONSE;
>>>>>>> Stashed changes
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    if (req.id == SIGNUP_RESPONSE)
    {
        SignupResponse res;
<<<<<<< Updated upstream
        res.status = (int)req.buffer.get();
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    LoginRequestHandler* log = new LoginRequestHandler();
    //returnReq.newHandler = log;
    return returnReq;
}
=======
        SignupRequest signReq = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);


        //Here we will handle the request and check if everything is valid

        
        res.status = VALID_RESPONSE;
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    IRequestHandler* log = new LoginRequestHandler(); //we will change it later to another handler
    returnReq.newHandler = log;
    return returnReq;
}
>>>>>>> Stashed changes
>>>>>>> Stashed changes
