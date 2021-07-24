//
// Created by natri on 7/22/2021.
//

#ifndef MESSENGER_TCPSERVER_H
#define MESSENGER_TCPSERVER_H

#include <atomic>
#include <map>
#include "../../core/socket/SocketConnector.h"
#include "handler/ClientHandler.h"

enum class ServerStatus : uint8_t {
    ON = 1,
    OFF = 0
};

class TCPServer : protected SocketConnector {
public:

    ~TCPServer();

    void startServer();

    void stopServer();

    ServerStatus getServerStatus() { return status.load(memory_order_relaxed); }

private:
    atomic<ServerStatus> status = ServerStatus::OFF;
    SOCKET listenSocket = INVALID_SOCKET;
    map<string, ClientHandler> clients;

    void handleNewConnections();

    ServerStatus setServerStatus(ServerStatus newStatus) {
        status.exchange(newStatus, memory_order_relaxed);
        return getServerStatus();
    }
};


#endif //MESSENGER_TCPSERVER_H
