//
// Created by natri on 7/22/2021.
//

#ifndef MESSENGER_CLIENTHANDLER_H
#define MESSENGER_CLIENTHANDLER_H

#include "../../../core/socket/SocketConnector.h"

class ClientHandler : public SocketConnector {

public:

    explicit ClientHandler(SOCKET socket) : SocketConnector(), clientSocket{socket} {}

    void operator()() { handleReadFromClient();}

private:

    SOCKET clientSocket;

    void handleReadFromClient();

};


#endif //MESSENGER_CLIENTHANDLER_H
