//
// Created by natri on 7/22/2021.
//

#ifndef MESSENGER_TCPSERVER_H
#define MESSENGER_TCPSERVER_H

#include "../../core/socket/SocketConnector.h"
#include "handler/ClientHandler.h"
#include <atomic>

using namespace std;

enum class ServerStatus : uint8_t {
    ON = 1,
    OFF = 0
};

class TCPServer : protected SocketConnector {
public:

    ~TCPServer();

    void startServer();

    void stopServer();

    ServerStatus getServerStatus() { return status; }

private:
    atomic<ServerStatus> status = ServerStatus::OFF;
    SOCKET listenSocket = INVALID_SOCKET;

    void handleNewConnections();
};


#endif //MESSENGER_TCPSERVER_H
