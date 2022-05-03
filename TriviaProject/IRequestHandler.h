#pragma once

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

};

