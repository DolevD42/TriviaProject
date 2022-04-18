#pragma once
#include <memory>
#include <string>
#include "json.hpp"
using nlohmann::json;

typedef struct LoginRequest {
	std::string username;
	std::string password;
} LoginResponse;

typedef struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
} SignupResponse;

class JsonResponsePacketSerializer {
public:
	static LoginRequest deserializLoginRequest(std::unique_ptr<char[]>);
	static SignupRequest deserializeSingupRequest(std::unique_ptr<char[]>);
};
