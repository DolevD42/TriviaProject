#include "Response.h"

std::unique_ptr<char[]> JsonResponsePacketSerializer::serializeResponse(ErrorResponse msgType)
{

	std::string js = "{message: "+(char)34+ msgType.message +(char)34+"}";
	return onlyStatus(ERR_CODE, sizeof(js.c_str()), js.c_str());
}

std::unique_ptr<char[]> JsonResponsePacketSerializer::serializeResponse(LoginResponse msgType)
{
	std::string js = "{status: " + std::to_string(msgType.status) + "}";
	return onlyStatus(LOGIN_CODE, sizeof(js.c_str()), js.c_str());
}

std::unique_ptr<char[]> JsonResponsePacketSerializer::serializeResponse(SignupResponse msgType)
{
	std::string js = "{status: " + std::to_string(msgType.status) + "}";
	return onlyStatus(SIGNUP_RESPONSE, sizeof(js.c_str()) , js.c_str());
}

std::unique_ptr<char[]> JsonResponsePacketSerializer::onlyStatus(int code, int len, const void* info)
{
	std::unique_ptr<char[]> toReturn(new char[BASIC_LEN + len]);
	toReturn[MSG_TYPE] = code;
	memcpy(toReturn.get() + SKIP_TYPE, &len, sizeof(int));
	memcpy(toReturn.get() + BASIC_LEN, info, len);
	return toReturn;
}