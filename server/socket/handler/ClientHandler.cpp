//
// Created by natri on 7/22/2021.
//

#include "ClientHandler.h"

void ClientHandler::handleReadFromClient() {
    int iResult;

    char recvbuf[DEFAULT_BUFFER];
    int recvbuflen = DEFAULT_BUFFER;

    do {
        iResult = recv(clientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            wprintf(L"Bytes received: %d\n", iResult);
        else if (iResult == 0)
            wprintf(L"Connection closed\n");
        else
            wprintf(L"recv failed: %d\n", WSAGetLastError());

    } while (iResult > 0);

    closesocket(clientSocket);
}
