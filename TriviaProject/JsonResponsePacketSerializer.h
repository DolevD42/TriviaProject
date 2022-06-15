#pragma once
#include <memory>
#include <string>
#include <math.h>
#include <vector>
#include "Helper.h"
#include "json.hpp"
#include "RoomManager.h"
using nlohmann::json;
#define BASIC_LEN 1 + sizeof(int)
#define MSG_LEN 4
#define SKIP_TYPE 1
#define MSG_TYPE 0
#define END 1



typedef struct LoginResponse {
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
	unsigned int status;
} SignupResponse;

typedef struct LogoutResponse {
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct GetHighScoreResponse {
	unsigned int status;
	std::vector<std::string> statistics;
} GetHighScoreResponse;

typedef struct GetPersonalStatsResponse {
	unsigned int status;
	std::vector<std::string> statistics;
} GetPersonalStatsResponse;

typedef struct JoinRoomResponse {
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse {
	unsigned int status;
} CreateRoomResponse;

typedef struct CloseRoomResponse {
	unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse {
	unsigned int status;
} StartGameResponse;

typedef struct GetRoomStateResponse {
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	float answerTimeOut;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse {
	unsigned int status;
} LeaveRoomResponse;

typedef struct GetQuestionResponse {
	unsigned int status;
	std::string Question;
	std::map<unsigned int, std::string> answers;
} GetQuestionResponse;

typedef struct SubmitAnswerResponse {
	unsigned int status;
	unsigned int CorrectAnswerId;
} SubmitAnswerResponse;

typedef struct PlayerResult {
	unsigned int CorrectAnswerCount;
	unsigned int WrongeAnswerCount;
	unsigned int AverageAnswerTime;
	std::string userName;
} PlayerResult;

typedef struct GetGameResultResponse {
	unsigned int status;
	std::vector<PlayerResult> Results;
} GetGameResultResponse;

typedef struct ErrorResponse {
	std::string message;
} ErrorResponse;

class JsonResponsePacketSerializer {
public:
	static std::vector<char> serializeResponse(ErrorResponse msg);
	static std::vector<char> serializeResponse(LoginResponse msg);
	static std::vector<char> serializeResponse(SignupResponse msg);
	static std::vector<char> serializeResponse(LogoutResponse msg);
	static std::vector<char> serializeResponse(GetRoomsResponse msg);
	static std::vector<char> serializeResponse(GetPlayersInRoomResponse msg);
	static std::vector<char> serializeResponse(JoinRoomResponse msg);
	static std::vector<char> serializeResponse(CreateRoomResponse msg);
	static std::vector<char> serializeResponse(GetHighScoreResponse msg);
	static std::vector<char> serializeResponse(GetPersonalStatsResponse msg);
	static std::vector<char> serializeResponse(CloseRoomResponse msg);
	static std::vector<char> serializeResponse(StartGameResponse msg);
	static std::vector<char> serializeResponse(GetRoomStateResponse msg);
	static std::vector<char> serializeResponse(LeaveRoomResponse msg);
private:
	static std::vector<char> onlyStatus(int code, int len, std::string info);
};