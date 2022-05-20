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
typedef struct LoginResponse {
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse {
	std::string message;
} ErrorResponse;

class JsonResponsePacketSerializer {
public:
	static std::vector<char> serializeResponse(ErrorResponse msg);
	static std::vector<char> serializeResponse(LoginResponse msg);
	static std::vector<char> serializeResponse(SignupResponse msg);
private:
	static std::vector<char> onlyStatus(int code, int len, std::string info);
};