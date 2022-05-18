#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager* loginManager, RequestHandlerFactory* handlerFactory)
{
    this->m_handlerFactory = handlerFactory;
    this->m_loginManager = loginManager;
}

LoginRequestHandler::~LoginRequestHandler()
{
    delete m_loginManager;
}

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
        ErrorResponse res;
        res.message = "INVALID CODE";
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
        return returnReq;
    }
    if (req.id == LOGIN_CODE)
    {
        returnReq = login(req);
    }
    if (req.id == SIGNUP_RESPONSE)
    {
        returnReq = signup(req);
    }
    return returnReq;
}

RequestResult LoginRequestHandler::login(const RequestInfo& req)
{
    int funcCode;
    RequestResult returnReq;
    
    LoginRequest logReq = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
    funcCode = m_loginManager->login(logReq.username, logReq.password);
    if (funcCode == REQUEST_VALID)
    {
        LoginResponse res;
        res.status = VALID_RESPONSE;
        returnReq.newHandler = this; //change this later
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    else
    {
        ErrorResponse res;
        if (funcCode == USER_DONT_EXIST)
        {
            res.message = "User don't exist";
        }
        if (funcCode == PASSWORD_DONT_MATCH)
        {
            res.message = "The password don't match the username";
        }
        if (funcCode == USER_ALREADY_LOGIN)
        {
            res.message = "User already logged in";
        }
        returnReq.newHandler = this;
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }

    return returnReq;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& req)
{
    int funcCode;
    RequestResult returnReq;
    SignupRequest signReq = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);
    funcCode = m_loginManager->signup(signReq.username, signReq.password, signReq.email);
    if (funcCode == REQUEST_VALID)
    {
        SignupResponse res;
        res.status = VALID_RESPONSE;
        returnReq.newHandler = this;
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    else
    {
        ErrorResponse res;
        if (funcCode == USER_ALREADY_EXIST)
        {
            res.message = "Username already taken";
        }
        returnReq.newHandler = this;
        returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    }
    
    return returnReq;
}
