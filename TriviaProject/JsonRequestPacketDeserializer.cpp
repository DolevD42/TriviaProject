#include "JsonRequestPacketDeserializer.h"


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> buffer)
{
    LoginRequest req;
    std::string str;
    str = Helper::fromVectToString(buffer);
    json j = json::parse(str);
    req.username = j["username"];
    req.password = j["password"];
    return req;
}


SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> buffer)
{
    SignupRequest req;
    std::string str;
    str = Helper::fromVectToString(buffer);
    json j = json::parse(str);
    req.username = j["username"];
    req.password = j["password"];
    req.email = j["email"];
    return req;
}
