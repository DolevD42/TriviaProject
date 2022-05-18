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
        std::vector<char> vec;
        returnReq.response = vec; //change this later
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
    RequestResult returnReq;
    LoginResponse res;
    LoginRequest logReq = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
    m_loginManager->login(logReq.username, logReq.password);

    res.status = VALID_RESPONSE;
    returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    returnReq.newHandler = this;
    return returnReq;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& req)
{
    RequestResult returnReq;
    SignupResponse res;
    SignupRequest signReq = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);


    m_loginManager->signup(signReq.username, signReq.password, signReq.email);

    res.status = VALID_RESPONSE;
    returnReq.response = JsonResponsePacketSerializer::serializeResponse(res);
    returnReq.newHandler = this;
    return returnReq;
}
