//
// Created by natri on 7/22/2021.
//

#include "SocketConnector.h"

void SocketConnector::wsaStartup() {
    if (int result = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        wprintf(L"WSAStartup failed with error: %ld\n", result);
        throw std::runtime_error(std::string("WSAStartup failed with error"));
    }
}

void SocketConnector::closeAndPrintWSAError(const wchar_t *const message, const SOCKET *socket) {
    wprintf(message, WSAGetLastError());
    close(socket);
}

SOCKET SocketConnector::createListenSocket(int af, int type, int protocol) {
    SOCKET listenerSocket = socket(af, type, protocol);
    if (listenerSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    return listenerSocket;
}

void SocketConnector::close(const SOCKET *socket) {
    WSACleanup();
    if (*socket != NULL) {
        closesocket(*socket);
    }
}
