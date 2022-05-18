#pragma once
#include <string>
class IDataBase
{
public:
	virtual bool doesUserExist(std::string userName) = 0;
	virtual bool doesPasswordMatch(std::string userName, std::string pass) = 0;
	virtual void addNewUser(std::string userName, std::string pass, std::string email) = 0;
};

