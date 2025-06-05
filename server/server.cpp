#include "server.hpp"




int setUpConnection(SOCKET& ClientSocket)
{
    WSADATA wsaData;
    int iResult;
    
    SOCKET ListenSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    /*
    int iSendResult;
    char recvbuf[DEFAULT_BUF_LENGTH];
    int recvbuflen = DEFAULT_BUF_LENGTH;
    */

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // Use IPv4
    hints.ai_socktype = SOCK_STREAM; // Stream socket
    hints.ai_protocol = IPPROTO_TCP; // TCP protocol
    hints.ai_flags = AI_PASSIVE; // Use my IP

    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a socket for the server to listen for client connections
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    // Listen for incoming connections
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);
    return 0;
}

int closeConnection(SOCKET& ClientSocket)
{
    // Shutdown the connection since we're done
    int iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // Cleanup Winsock
    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}

bool receiveMessage(SOCKET& ClientSocket, std::string& message)
{
    bool success = true;
    char recvbuf[DEFAULT_BUF_LENGTH];
    int recvbuflen = DEFAULT_BUF_LENGTH;
    int iResult = 0;
    while (iResult == 0)
    {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            message = std::string(recvbuf, iResult);
        } else if (iResult == 0) {
            Sleep(500); // Wait for 500 milliseconds before trying again
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            success = false; // Set success to false if there was an error
        }
    }

    return success; // Return true if successful, false if there was an error
}

bool sendMessage(SOCKET ClientSocket, const char* message)
{
    bool success = true;

    int iResult = send(ClientSocket, message, (int)strlen(message), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        success = false;
    } else {
        printf("Bytes Sent: %d\n", iResult);
    }

    return success; // Return 0 if successful, 1 if there was an error
}

/*
int main()
{
    SOCKET ClientSocket = INVALID_SOCKET;
    int result = setUpConnection(ClientSocket);
    if (result != 0) {
        return result;
    }

    int numBytesReceived = 0;
    int numBytesSent = 0;
    char recvbuf[DEFAULT_BUF_LENGTH];
    int recvbuflen = DEFAULT_BUF_LENGTH;

    // Receive until the peer shuts down the connection
    do {
        numBytesReceived = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (numBytesReceived > 0) {
            printf("Bytes received: %d\n", numBytesReceived);
            printf("Received data: %.*s\n", numBytesReceived, recvbuf);
            // Echo the buffer back to the sender
            numBytesSent = send(ClientSocket, recvbuf, numBytesReceived, 0);
            if (numBytesSent == SOCKET_ERROR) {
                printf("send failed: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", numBytesSent);
        } else if (numBytesReceived == 0) {
            printf("Connection closed\n");
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
        }
    } while (numBytesReceived > 0);

    result = closeConnection(ClientSocket);
    if (result != 0) {
        return result;
    }
    return 0;
}
*/

int main()
{
    SOCKET ClientSocket = INVALID_SOCKET;
    int result = setUpConnection(ClientSocket);
    if (result != 0) {
        return result;
    }

    std::string message;
    while (receiveMessage(ClientSocket, message)) {
        std::cout << "Received: " << message << std::endl;
        if (message == "exit") {
            break; // Exit the loop if the message is "exit"
        }
    }

    result = closeConnection(ClientSocket);
    if (result != 0) {
        return result;
    }
    
    return 0;
}