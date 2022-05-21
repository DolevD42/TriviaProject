#pragma once
#include <memory>
#include <string>
#include "Helper.h"
#include "json.hpp"
#include <bitset>
#define CODE_END 1
#define DATALEN_LEN 4
using nlohmann::json;
typedef std::vector<std::bitset<8>> aVec;
typedef struct LoginRequest {
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;

typedef struct GetPlayersInRoomRequest {
	unsigned int roomId;
} GetPlayersInRoomRequest;
typedef struct JoinRoomRequest {
	unsigned int roomId;
} JoinRoomRequest;
typedef struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
} CreateRoomRequest;
typedef struct SubmitAnswerRequest {
	unsigned int answerId;
} SubmitAnswerRequest;


class JsonRequestPacketDeserializer {
	static std::string extractData(const aVec& data);
public:
	static LoginRequest deserializeLoginRequest(std::vector<char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<char> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const aVec& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const aVec& buffer);
	static CreateRoomRequest deserializeCreateRoomReuquest(const aVec& buffer);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(const aVec& buffer);

};
void printPtr(const aVec& ptr, const unsigned int len);
aVec slice(const aVec& str, const unsigned int start, const unsigned int len);
