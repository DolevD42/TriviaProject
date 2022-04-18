#pragma once
#include <memory>
#include <string>
#include "json.hpp"
using nlohmann::json;

typedef struct LoginRequest {
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;

class JsonResponsePacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(std::unique_ptr<char[]>);
	static SignupRequest deserializeSingupRequest(std::unique_ptr<char[]>);
};
