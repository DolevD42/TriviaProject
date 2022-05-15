#include "Response.h"
#define ZERO 126

std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse msgType)
{
	json j;
	j["message"] = msgType.message;
	std::string js = j.dump();
	return onlyStatus(ERR_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse msgType)
{
	json j;
	j["status"] = msgType.status;
	std::string js = j.dump();
	return onlyStatus(LOGIN_CODE, js.length(), js);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse msgType)
{
	json j;
	j["status"] = msgType.status;
	std::string js = j.dump();
	return onlyStatus(SIGNUP_RESPONSE, js.length(), js);
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