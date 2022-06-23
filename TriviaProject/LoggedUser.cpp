#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string userName, SOCKET socket): m_username(userName), m_socket(socket)
{
}

std::string LoggedUser::getUsername()
{
    return m_username;
}

SOCKET LoggedUser::getSocket()
{
    return m_socket;
}
