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

<<<<<<< Updated upstream
class JsonResponsePacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(std::unique_ptr<char[]>);
	static SignupRequest deserializeSingupRequest(std::unique_ptr<char[]>);
=======
class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(std::vector<char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<char> buffer);
>>>>>>> Stashed changes
};
