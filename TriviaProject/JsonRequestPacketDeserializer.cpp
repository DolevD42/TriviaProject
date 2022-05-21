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

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const aVec& buffer)
{
    GetPlayersInRoomRequest request;
    std::string data = JsonRequestPacketDeserializer::extractData(buffer);
    nlohmann::json jsonObj = nlohmann::json::parse(data);
    unsigned int tempStr = jsonObj.value("roomId", 0);
    request.roomId = tempStr;
    return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const aVec& buffer)
{
    JoinRoomRequest request;
    std::string data = JsonRequestPacketDeserializer::extractData(buffer);
    nlohmann::json jsonObj = nlohmann::json::parse(data);
    unsigned int tempStr = jsonObj.value("roomId", 0);
    request.roomId = tempStr;
    return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomReuquest(const aVec& buffer)
{
    CreateRoomRequest request;
    std::string data = JsonRequestPacketDeserializer::extractData(buffer);
    nlohmann::json jsonObj = nlohmann::json::parse(data);
    std::string tempStr = std::string(jsonObj.value("roomName", "unknown"));
    request.roomName = tempStr;
    unsigned int tempNum = jsonObj.value("maxUsers", 0);
    request.maxUsers = tempNum;
    tempNum = jsonObj.value("questionCount", 0);
    request.questionCount = tempNum;
    tempNum = jsonObj.value("answerTimeout", 0);
    request.answerTimeout = tempNum;
    tempNum = jsonObj.value("questionCount", 0);
    request.questionCount = tempNum;
    return request;

}

std::string JsonRequestPacketDeserializer::extractData(const aVec& buffer)
{
    unsigned int len = 0;
    aVec sliced = slice(buffer, CODE_END, DATALEN_LEN);
    std::string toRet = "";
    memcpy(&len, sliced.data(), DATALEN_LEN);
    sliced = slice(buffer, CODE_END + DATALEN_LEN, len);
    for (unsigned int i = 0; i < len; i++) {
        toRet += (char)sliced[i].to_ulong();
    }
    return toRet;

}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const aVec& buffer)
{
    SubmitAnswerRequest request;
    std::string data = JsonRequestPacketDeserializer::extractData(buffer);
    nlohmann::json jsonObj = nlohmann::json::parse(data);
    unsigned int tempStr = jsonObj.value("answerId", 0);
    request.answerId = tempStr;
    return request;

}

void printPtr(const aVec& ptr, const unsigned int len)
{
    printf("\n");
    for (unsigned int i = 0; i < len; i++)
    {
        printf("%u ", (unsigned char)ptr[i].to_ulong());
    }
}

aVec slice(const aVec& str, const unsigned int start, const unsigned int len)
{
    aVec sliced(len);
    for (unsigned int i = 0; i < len; i++) {
        sliced[i] = (char)str[i + start].to_ulong();
    }
    return sliced;

}
