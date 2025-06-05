#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int setUpConnection(SOCKET& ConnectSocket, int argc, char** argv)
{
    printf("Client started\n");
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    

    WSADATA wsaData;
    struct addrinfo *result = NULL,
        *ptr = NULL,
        hints;
    const char *sendbuf = "this is a test";
    //char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    //int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // Use IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Stream socket
    hints.ai_protocol = IPPROTO_TCP; // TCP protocol

    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        
        // Create a socket for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed: %d\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result); // No longer need the address info

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %d\n", iResult);
    return 0;
}

void closeConnection(SOCKET& ConnectSocket)
{
    int iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    } else {
        printf("Connection closed successfully.\n");
    }
}

void receiveMessage(SOCKET& ConnectSocket)
{
    int numBytesReceived = 0;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Receive until the peer closes the connection
    do {
        numBytesReceived = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (numBytesReceived > 0) {
            printf("Bytes received: %d\n", numBytesReceived);
            printf("Received data: %.*s\n", numBytesReceived, recvbuf);
        } else if (numBytesReceived == 0) {
            printf("Connection closed\n");
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
        }
    } while (numBytesReceived > 0);
}

/*
int main(int argc, char** argv)
{

    SOCKET ConnectSocket = INVALID_SOCKET;
    int result = setUpConnection(ConnectSocket, argc, argv);
    if (result != 0) {
        printf("setUpConnection failed: %d\n", result);
        return 1;
    }

    // Receive until the peer closes the connection
    result = shutdown(ConnectSocket, SD_SEND);
    if (result == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    int numBytesReceived = 0;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN; 
    do {
        numBytesReceived = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (numBytesReceived > 0)
            printf("Bytes received: %d\n", numBytesReceived);
        else if (numBytesReceived == 0)
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());
    } while (numBytesReceived > 0);

    // Cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}
*/