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

#define ERR_CODE 41
#define LOGIN_CODE 42
#define SIGNUP_CODE 43
#define LOGOUT_CODE 44
#define GET_ROOMS_CODE 45
#define GET_PLAYERS_CODE 46
#define GET_HIGH_CODE 47
#define GET_PERSONAL_CODE 48
#define JOIN_ROOM_CODE 49
#define CREATE_ROOM_CODE 50

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
private:
	static std::vector<char> onlyStatus(int code, int len, std::string info);
};