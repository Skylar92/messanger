#include "ClientSocketConnector.h"

void ClientSocketConnector::setupConnection() {
    WSADATA wsaData;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        throw std::runtime_error(std::string("WSAStartup failed with error"));
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("Failed connecting to server: %d\n", iResult);
        WSACleanup();
        throw std::runtime_error(std::string("Failed connecting to server"));
    }

    ptr = result;

    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                           ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        throw std::runtime_error(std::string("Error at socket"));
    }

    iResult = connect(ConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        throw std::runtime_error(std::string("Unable to connect to server"));
    }
}

void ClientSocketConnector::sendMessage(const char *message) {
    int recvbuflen = DEFAULT_BUFFER;
    char recvbuf[DEFAULT_BUFFER];

    // Send an initial buffer
    iResult = send(ConnectSocket, message, (int) strlen(message), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
}

ClientSocketConnector::~ClientSocketConnector() {
    iResult = shutdown(ConnectSocket, SD_SEND);
    closesocket(ConnectSocket);
    WSACleanup();
}

void ClientSocketConnector::listening(std::function<void(std::string)> callback) {
    if (callback != nullptr) {
        char recvbuf[DEFAULT_BUFFER];
        int recvbuflen = DEFAULT_BUFFER;

        do {
            iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
            if (iResult > 0) {
                callback("sdds");
                printf("Bytes received: %d\n", iResult);
            } else if (iResult == 0)
                printf("Connection closed\n");
            else
                printf("recv failed: %d\n", WSAGetLastError());
        } while (iResult > 0);
    }
}
