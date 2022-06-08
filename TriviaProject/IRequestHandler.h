#pragma once

#include <time.h>
#include <string>
#include <memory>
#include <vector>
#include <ctime>
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "structDef.h"


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo req) = 0;
	virtual RequestResult handleRequest(RequestInfo req) = 0;
protected:
	SOCKET m_socket;
};

