#ifndef SERVER_HPP
#define SERVER_HPP

#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUF_LENGTH 512
#define DEFAULT_PORT "27015"

#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

int setUpConnection(SOCKET& ClientSocket);
int closeConnection(SOCKET& ClientSocket);
bool receiveMessage(SOCKET& ClientSocket, std::string& message);
bool sendMessage(SOCKET& ClientSocket, const char* message);

#endif