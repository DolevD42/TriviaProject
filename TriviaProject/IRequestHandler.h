#pragma once
<<<<<<< Updated upstream
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

=======
<<<<<<< Updated upstream
class IRequestHandler
{
=======
#include <time.h>
#include <string>
#include <memory>
#include <vector>
#include <ctime>
#include "Response.h"
#include "Request.h"
#include "structDef.h"


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo req) = 0;
	virtual RequestResult handleRequest(RequestInfo req) = 0;

>>>>>>> Stashed changes
>>>>>>> Stashed changes
};

