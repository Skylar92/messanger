//
// Created by natri on 7/22/2021.
//

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

#ifndef MESSENGER_SOCKETCONNECTOR_H
#define MESSENGER_SOCKETCONNECTOR_H

#define DEFAULT_BUFFER 4096


class SocketConnector {

protected:
    WSADATA wsaData;

    void wsaStartup();

    void closeAndPrintWSAError(_In_z_ _Printf_format_string_ wchar_t const *message, const SOCKET *socket = nullptr);

    void close(const SOCKET *socket = nullptr);

    SOCKET createListenSocket(_In_ int af, _In_ int type, _In_ int protocol);

};


#endif //MESSENGER_SOCKETCONNECTOR_H
