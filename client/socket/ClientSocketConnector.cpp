#include "ClientSocketConnector.h"

void ClientSocketConnector::setupConnection() {

    wsaStartup();

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result) != 0) {
        closeAndPrintWSAError(L"Failed connecting to server: %d\n");
        throw std::runtime_error(std::string("Failed connecting to server"));
    }

    ptr = result;

    connectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                           ptr->ai_protocol);

    if (connectSocket == INVALID_SOCKET) {
        freeaddrinfo(result);
        closeAndPrintWSAError(L"Error at socket(): %d\n");
        throw std::runtime_error(std::string("Error at socket"));
    }

    if (connect(connectSocket, ptr->ai_addr, (int) ptr->ai_addrlen) == SOCKET_ERROR) {
        closeAndPrintWSAError(L"Error creation of socket: %d\n", &connectSocket);
        connectSocket = INVALID_SOCKET;
        throw std::runtime_error(std::string("Unable to connect to server"));
    }

    freeaddrinfo(result);

    sendMessage("hello_message");
}

void ClientSocketConnector::sendMessage(const char *message) {
    auto objMessage = Message(username, string(message));
    auto serializedObjMessage = serializeObject(objMessage);
    const char *serializedMessage = serializedObjMessage.c_str();

    if (send(connectSocket, serializedMessage, (int) strlen(serializedMessage), 0) == SOCKET_ERROR) {
        closeAndPrintWSAError(L"send failed: %d\n", &connectSocket);
    }
}

ClientSocketConnector::~ClientSocketConnector() {
    shutdown(connectSocket, SD_SEND);
    closesocket(connectSocket);
    WSACleanup();
}

void ClientSocketConnector::listening(const std::function<void(std::string)>& callback) {
    if (callback != nullptr) {
        char recvbuf[DEFAULT_BUFFER];
        int recvbuflen = DEFAULT_BUFFER;

        int res;
        do {
            res = recv(connectSocket, recvbuf, recvbuflen, 0);
            if (res > 0) {
                string serializedMessage(recvbuf, res);
                auto clientMessage = deserializeObject<Message>(serializedMessage);
                callback(clientMessage.text);
            } else if (res == 0)
                printf("Connection closed\n");
            else
                printf("recv failed: %d\n", WSAGetLastError());
        } while (res > 0);
    }
}
