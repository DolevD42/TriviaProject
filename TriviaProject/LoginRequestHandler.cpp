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
    if (req.id == LOGIN_CODE || req.id == SIGNUP_CODE)
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
    if (req.id == SIGNUP_CODE)
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
    LoginResponse res;
    res.status = funcCode;
    returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    if (funcCode == REQUEST_VALID)
    {
        MenuRequestHandler* newHand =  m_handlerFactory->createMenuRequestHandler();
        LoggedUser* newUser = new LoggedUser(logReq.username);
        newHand->setUser(newUser);
        returnReq.newHandler = newHand;
    }
    else
    {
        returnReq.newHandler = this;
    }
    
    return returnReq;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& req)
{
    int funcCode;
    RequestResult returnReq;
    SignupRequest signReq = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);
    funcCode = m_loginManager->signup(signReq.username, signReq.password, signReq.email);
    SignupResponse res;
    res.status = funcCode;
    returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    if (funcCode == REQUEST_VALID)
    {
        MenuRequestHandler* newHand = m_handlerFactory->createMenuRequestHandler();
        LoggedUser* newUser = new LoggedUser(signReq.username);
        newHand->setUser(newUser);
        returnReq.newHandler = newHand;
    }
    else
    {
        returnReq.newHandler = this;
    }
    
    return returnReq;
}
