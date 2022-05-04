#include "Response.h"

std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse msgType)
{
	json j;
	j["message"] = msgType.message;
	std::string js = j.dump();
	return onlyStatus(ERR_CODE, sizeof(js.c_str()), js.c_str());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse msgType)
{
	json j;
	j["status"] = msgType.status;
	std::string js = j.dump();
	return onlyStatus(LOGIN_CODE, sizeof(js.c_str()), js.c_str());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse msgType)
{
	json j;
	j["status"] = msgType.status;
	std::string js = j.dump();
	return onlyStatus(SIGNUP_RESPONSE, sizeof(js.c_str()) , js.c_str());
}


std::vector<char> JsonResponsePacketSerializer::onlyStatus(int code, int len, std::string info)
{
	std::vector<char> toReturn;
	int num = 0;
	toReturn.push_back((char)code);
	for (int i = 3; i >= 0; i--)
	{
		num = (int)len / (256^i);
		len = len - num;
		toReturn.push_back((char)num);
	}
	for (int i = 0; i < len; i++)
	{
		toReturn.push_back(info[i]);
	}
	return toReturn;
}