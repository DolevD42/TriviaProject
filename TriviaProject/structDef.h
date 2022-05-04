#pragma once
#include "IRequestHandler.h"

class IRequestHandler;

typedef struct RequestInfo {
	int id;
	time_t recievedTime;
	std::vector<char> buffer;
} RequestInfo;

typedef struct RequestResult {
	IRequestHandler* newHandler;
	std::vector<char> response;
} RequestResult;
