#pragma once
#include <memory>
#include <string>
#include "Helper.h"
#include "json.hpp"
#include <bitset>
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

class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(std::vector<char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<char> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const aVec& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const aVec& buffer);
	static CreateRoomRequest deserializeCreateRoomReuquest(const aVec& buffer);

};
