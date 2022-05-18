#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string userName): m_username(userName)
{
}

std::string LoggedUser::getUsername()
{
    return m_username;
}
