#include "Response.h"

std::unique_ptr<char[]> JsonResponsePacketSerializer::serializeResponse(ErrorResponse msgType)
{
	return onlyStatus(ERR_CODE, msgType.message.length(), msgType.message.c_str());
}

std::unique_ptr<char[]> JsonResponsePacketSerializer::serializeResponse(LoginResponse msgType)
{
	return onlyStatus(LOGIN_CODE, sizeof(int), &msgType.status);
}

std::unique_ptr<char[]> JsonResponsePacketSerializer::serializeResponse(SignupResponse msgType)
{
	return onlyStatus(SIGNUP_RESPONSE, sizeof(int), &msgType.status);
}

std::unique_ptr<char[]> JsonResponsePacketSerializer::onlyStatus(int code, int len, const void* info)
{
	std::unique_ptr<char[]> toReturn(new char[BASIC_LEN + len]);
	toReturn[MSG_TYPE] = code;
	memcpy(toReturn.get() + SKIP_TYPE, &len, sizeof(int));
	memcpy(toReturn.get() + BASIC_LEN, info, len);
	return toReturn;
}