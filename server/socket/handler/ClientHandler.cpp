//
// Created by natri on 7/22/2021.
//

#include "ClientHandler.h"

#include <utility>

void ClientHandler::handleReadFromClient() {
    int result;

    char recvbuf[DEFAULT_BUFFER];
    int recvbuflen = DEFAULT_BUFFER;

    do {
        result = recv(clientSocket, recvbuf, recvbuflen, 0);
        if (result > 0) {
            string serializedMessage(recvbuf, result);
            auto clientMessage = deserializeObject<Message>(serializedMessage);

            if (!userSaidHello) {
                onHelloMessageReceivedCallback(clientMessage, *this);
                userSaidHello = true;
            } else {
                onMessageReceivedCallback(clientMessage);
            }

        } else if (result == 0)
            wprintf(L"Connection closed\n");
        else
            wprintf(L"recv failed: %d\n", WSAGetLastError());

    } while (result > 0);

    closesocket(clientSocket);
}

void ClientHandler::sendTo(Message message) {
    auto serializedObjMessage = serializeObject(move(message));
    const char *serializedMessage = serializedObjMessage.c_str();

    if (send(clientSocket, serializedMessage, (int) strlen(serializedMessage), 0) == SOCKET_ERROR) {
        closeAndPrintWSAError(L"send failed: %d\n", &clientSocket);
    }
}
