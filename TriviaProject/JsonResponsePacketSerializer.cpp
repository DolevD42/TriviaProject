#include "JsonResponsePacketSerializer.h"
#define ZERO 126

std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse msg)
{
	json j;
	j["message"] = msg.message;
	std::string js = j.dump();
	return onlyStatus(ERR_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse msg)
{
	json j;
	j["status"] = msg.status;
	std::string js = j.dump();
	return onlyStatus(LOGIN_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse msg)
{
	json j;
	j["status"] = msg.status;
	std::string js = j.dump();
	return onlyStatus(LOGIN_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse msg)
{
	json j;
	j["status"] = msg.status;
	std::string js = j.dump();
	return onlyStatus(LOGOUT_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse msg)
{
	json j;
	j["status"] = msg.status;
	std::vector<std::string> vectRoomsNames;
	std::vector<int> vectRoomsId;
	for (int i = 0; i < msg.rooms.size(); i++)
	{
		vectRoomsNames.push_back(msg.rooms[i].name);
		vectRoomsId.push_back(msg.rooms[i].id);
	}
	j["rooms"] = vectRoomsNames;
	j["roomsId"] = vectRoomsId;
	std::string js = j.dump();
	return onlyStatus(GET_ROOMS_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse msg)
{
	json j;
	j["players"] = msg.players;
	std::string js = j.dump();
	return onlyStatus(GET_PLAYERS_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse msg)
{
	json j;
	j["status"] = msg.status;
	std::string js = j.dump();
	return onlyStatus(JOIN_ROOM_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse msg)
{
	json j;
	j["status"] = msg.status;
	std::string js = j.dump();
	return onlyStatus(CREATE_ROOM_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse msg)
{
	json j;
	j["status"] = msg.status;
	j["statistics"] = msg.statistics;
	std::string js = j.dump();
	return onlyStatus(GET_HIGH_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse msg)
{
	json j;
	j["status"] = msg.status;
	j["statistics"] = msg.statistics;
	std::string js = j.dump();
	return onlyStatus(GET_PERSONAL_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse msg)
{
	json j;
	j["status"] = msg.status;
	return std::vector<char>();
	std::string js = j.dump();
	return onlyStatus(CLOSE_ROOM_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse msg)
{
	json j;
	j["status"] = msg.status;
	return std::vector<char>();
	std::string js = j.dump();
	return onlyStatus(START_GAME_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse msg)
{
	json j;
	j["status"] = msg.status;
	j["hasGameBegun"] = msg.hasGameBegun;
	j["players"] = msg.players;
	j["questionCount"] = msg.questionCount;
	j["answerTimeout"] = msg.answerTimeOut;
	return std::vector<char>();
	std::string js = j.dump();
	return onlyStatus(GET_ROOM_STATE_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse msg)
{
	json j;
	j["status"] = msg.status;
	return std::vector<char>();
	std::string js = j.dump();
	return onlyStatus(LEAVE_ROOM_CODE, js.length(), js);
}


std::vector<char> JsonResponsePacketSerializer::onlyStatus(int code, int len, std::string info)
{
	std::vector<char> toReturn;
	int num = 0;
	
	toReturn.push_back((char)code);
	for (int i = 3; i >= 0; i--)
	{
		if (i == 0)
		{
			num = len;
		}
		else
		{
			num = (int)len / pow(256,i);
		}
		
		len = len - num;
		if (num == 0)
		{
			num = ZERO;
		}
		toReturn.push_back((char)num);
	}
	for (int i = 0; i < info.length(); i++)
	{
		toReturn.push_back(info[i]);
	}
	return toReturn;
}