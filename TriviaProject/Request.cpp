#include "Request.h"

LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(std::unique_ptr<char[]> buffer)
{
    LoginRequest req;
    std::string str = buffer.get();
    json j = str;
    req.username = j["username"];
    req.password = j["password"];
    return req;
}

SignupRequest JsonResponsePacketDeserializer::deserializeSingupRequest(std::unique_ptr<char[]> buffer)
{
    SignupRequest req;
    std::string str = buffer.get();
    json j = str;
    req.username = j["username"];
    req.password = j["password"];
    req.email = j["email"];
    return req;
}
