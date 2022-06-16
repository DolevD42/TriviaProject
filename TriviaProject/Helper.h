#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <WinSock2.h>

#define LEAVE_ROOM_CLIENT_MSG "6~~~~"
#define START_GAME_CLIENT_MSG "5~~~~"


#define ERR_CODE 41
#define LOGIN_CODE 42
#define SIGNUP_CODE 43
#define LOGOUT_CODE 44
#define GET_ROOMS_CODE 45
#define GET_PLAYERS_CODE 46
#define GET_HIGH_CODE 47
#define GET_PERSONAL_CODE 48
#define JOIN_ROOM_CODE 49
#define CREATE_ROOM_CODE 50
#define CLOSE_ROOM_CODE 51
#define START_GAME_CODE 52
#define GET_ROOM_STATE_CODE 53
#define LEAVE_ROOM_CODE 54
	#define GET_GAME_CODE 55
	#define SUBMIT_ANSWER_CODE 56
	#define GET_QUESTION_CODE 57
	#define LEAVE_GAME_CODE 58

#define PASSWORD_DONT_MATCH 41
#define REQUEST_VALID 42
#define USER_ALREADY_EXIST 43
#define USER_DONT_EXIST 44
#define USER_ALREADY_LOGIN 45
#define ROOM_DONT_EXIST 46
#define ROOM_MAX_OUT 47
#define WRONG_PARAMETERS 48

//room defention
#define ACTIVE_STATE 42
#define NON_ACTIVE_STATE 43
#define GAME_STARTED_STATE 44

enum MessageType : byte
{
	MT_CLIENT_LOG_IN = 200,
	MT_CLIENT_UPDATE = 204,
	MT_CLIENT_FINISH = 207,
	MT_CLIENT_EXIT = 208,
	MT_SERVER_UPDATE = 101,
};


class Helper
{
public:


	static int getMessageTypeCode(const SOCKET sc);
	static int getIntPartFromSocket(const SOCKET sc, const int bytesNum);
	static std::string getStringPartFromSocket(SOCKET sc, const int bytesNum);
	static void sendData(const SOCKET sc, const std::string message);
	static void send_update_message_to_client(const SOCKET sc, const std::string& file_content, const std::string& second_username, const std::string& all_users);
	static std::string getPaddedNumber(const int num, const int digits);
	static std::string fromVectToString(const std::vector<char> vect);
	static std::vector<char> fromStringToVector(const std::string str);
private:
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum);
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags);

};


#ifdef _DEBUG // vs add this define in debug mode
#include <stdio.h>
// Q: why do we need traces ?
// A: traces are a nice and easy way to detect bugs without even debugging
// or to understand what happened in case we miss the bug in the first time
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
// for convenient reasons we did the traces in stdout
// at general we would do this in the error stream like that
// #define TRACE(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__);

#else // we want nothing to be printed in release version
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define TRACE(msg, ...) // do nothing
#endif