#include "Request.h"

<<<<<<< Updated upstream
LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(std::unique_ptr<char[]> buffer)
{
    LoginRequest req;
    std::string str = buffer.get();
=======
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> buffer)
{
    LoginRequest req;
    std::string str;
    for (int i = 0; i < buffer.size(); i++)
    {
        str[i] = buffer[i];
    }
>>>>>>> Stashed changes
    json j = str;
    req.username = j["username"];
    req.password = j["password"];
    return req;
}

<<<<<<< Updated upstream
SignupRequest JsonResponsePacketDeserializer::deserializeSingupRequest(std::unique_ptr<char[]> buffer)
{
    SignupRequest req;
    std::string str = buffer.get();
=======
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> buffer)
{
    SignupRequest req;
    std::string str;
    for (int i = 0; i < buffer.size(); i++)
    {
        str[i] = buffer[i];
    }
>>>>>>> Stashed changes
    json j = str;
    req.username = j["username"];
    req.password = j["password"];
    req.email = j["email"];
    return req;
}
