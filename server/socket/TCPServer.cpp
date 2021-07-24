//
// Created by natri on 7/22/2021.
//

#define DEFAULT_PORT 27015
#define DEFAULT_HOST "127.0.0.1"

#include "TCPServer.h"

void TCPServer::startServer() {
    wsaStartup();
    listenSocket = createListenSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in service{};
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(DEFAULT_HOST);
    service.sin_port = htons(DEFAULT_PORT);

    if (::bind(listenSocket, (SOCKADDR *) &service, sizeof(service)) == SOCKET_ERROR ||
        listen(listenSocket, 1) == SOCKET_ERROR) {
        closeAndPrintWSAError(L"bind failed with error: %ld\n", &listenSocket);
        throw runtime_error(std::string("bind failed with error"));
    }

    setServerStatus(ServerStatus::ON);

    wprintf(L"Server started on %d port\n", DEFAULT_PORT);

    handleNewConnections();
}

void TCPServer::stopServer() {
    close(&listenSocket);
    status = setServerStatus(ServerStatus::OFF);
}

void TCPServer::handleNewConnections() {
    do {
        wprintf(L"Waiting for new connections...\n");
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);

        if (clientSocket == INVALID_SOCKET) {
            closeAndPrintWSAError(L"accept failed with error: %ld", &listenSocket);
            break;
        } else {
            wprintf(L"New client connected.\n");
            auto onMessageReceivedCallBack = [=](const Message &message) -> void {
                for (auto & client : clients) {
                    if (client.first != message.username) {
                        client.second.sendTo(message);
                    }
                }
            };

            auto onHelloMessageReceivedCallback = [=](const Message &message,
                                                      const ClientHandler &clientHandler) -> void {
                clients.insert(pair(message.username, clientHandler));
            };

            auto clientHandler = (ClientHandler(clientSocket, onMessageReceivedCallBack,
                                                onHelloMessageReceivedCallback));
            // run separate thread for handleReadFromClient client operations
            thread handleNewClientThread(clientHandler);
            handleNewClientThread.detach();
        }
    } while (getServerStatus() == ServerStatus::ON);
}

TCPServer::~TCPServer() {
    if (getServerStatus() == ServerStatus::ON) {
        stopServer();
    }
}

