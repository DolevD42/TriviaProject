#pragma once
#include <time.h>
#include <string>
#include <memory>
#include "Response.h"

typedef struct RequestInfo {
	int id;
	time_t recievedTime;
	std::unique_ptr<char[]> buffer;
} RequestInfo;

typedef struct RequestResult {
	//IRequestHandler* newHandler;
	std::unique_ptr<char[]> response;
} RequestResult;


class IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo req);
	RequestResult handleRequest(RequestInfo req);

};

