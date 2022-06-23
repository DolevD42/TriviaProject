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
    std::string str = Helper::fromVectToString(buffer);
    str = Helper::fromVectToString(buffer);
    json j = json::parse(str);
    req.username = j["username"];
    req.password = j["password"];
    req.email = j["email"];
    
    return req;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<char> buffer)
{
    GetPlayersInRoomRequest request;
    std::string data = Helper::fromVectToString(buffer);
    json jsonObj = json::parse(data);     
    request.roomId = jsonObj["roomId"];
    return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<char> buffer)
{
    JoinRoomRequest request;
    std::string data = Helper::fromVectToString(buffer);
    json jsonObj = json::parse(data);
    request.roomId = jsonObj["roomId"];
    return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<char> buffer)
{
    CreateRoomRequest request;
    std::string data= Helper::fromVectToString(buffer);
    json jsonObj = json::parse(data);
    request.roomName = jsonObj["roomName"];
    request.maxUsers = jsonObj["maxUsers"];
    request.questionCount = jsonObj["questionCount"];
    request.answerTimeout = jsonObj["answerTimeout"];
    return request;
}


SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(std::vector<char> buffer)
{
    SubmitAnswerRequest request;
    std::string data = Helper::fromVectToString(buffer);
    json jsonObj = json::parse(data);
    request.answerId = jsonObj["id"];
    request.timePerAns = jsonObj["timePerAns"];
    return request;

}

