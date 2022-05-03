#include "Request.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> buffer)
{
    LoginRequest req;
    std::string str;
    for (int i = 0; i < buffer.size(); i++)
    {
        str[i] = buffer[i];
    }
    json j = str;
    req.username = j["username"];
    req.password = j["password"];
    return req;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> buffer)
{
    SignupRequest req;
    std::string str;
    for (int i = 0; i < buffer.size(); i++)
    {
        str[i] = buffer[i];
    }
    json j = str;
    req.username = j["username"];
    req.password = j["password"];
    req.email = j["email"];
    return req;
}

