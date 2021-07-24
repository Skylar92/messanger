//
// Created by natri on 7/22/2021.
//

#ifndef MESSENGER_CLIENTHANDLER_H
#define MESSENGER_CLIENTHANDLER_H

#include <utility>

#include "../../../core/socket/SocketConnector.h"
#include "../../../core/socket/dto/Message.h"
#include "../../../core/socket/utils/SerializationUtils.h"

class ClientHandler : public SocketConnector {

public:

    explicit ClientHandler(SOCKET socket,
                           function<void(Message)> onMessageReceivedCallback,
                           function<void(Message, ClientHandler)> onHelloMessageReceivedCallback) : SocketConnector() {
        this->clientSocket = socket;
        this->onMessageReceivedCallback = move(onMessageReceivedCallback);
        this->onHelloMessageReceivedCallback = move(onHelloMessageReceivedCallback);
    }

    void operator()() { handleReadFromClient(); }

    void sendTo(Message message);

private:

    SOCKET clientSocket;
    bool userSaidHello = false;
    function<void(Message, ClientHandler)> onHelloMessageReceivedCallback;
    function<void(Message)> onMessageReceivedCallback;

    void handleReadFromClient();

};


#endif //MESSENGER_CLIENTHANDLER_H
