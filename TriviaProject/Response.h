#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Helper.h"
#include "json.hpp"
using nlohmann::json;
#define BASIC_LEN 1 + sizeof(int)
#define MSG_LEN 4
#define SKIP_TYPE 1
#define MSG_TYPE 0
#define ERR_CODE 0
#define LOGIN_CODE 1
#define SIGNUP_RESPONSE 2
#define END 1

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
	static std::vector<char> serializeResponse(ErrorResponse);
	static std::vector<char> serializeResponse(LoginResponse);
	static std::vector<char> serializeResponse(SignupResponse);
private:
	static std::vector<char> onlyStatus(int code, int len, std::string info);
};