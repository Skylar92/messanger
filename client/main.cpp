#include "socket/ClientSocketConnector.h"
#include <string>
#include <iostream>
#include <thread>

void listening(ClientSocketConnector *clientSocket) {
    clientSocket->listening(
            [](const std::string &message) -> void { printf("Message from backend %s", message.c_str()); });
}

int main() {

    auto *clientSocket = new ClientSocketConnector();
    clientSocket->setupConnection();

    std::string word;
    printf("Send messages or type EXIT to finish work\n");

    std::thread startListeningMessagesFromServer(listening, clientSocket);

    while (true) {
        printf("Message:");
        std::cin >> word;
        if (word != "EXIT") {
            const char *message = word.c_str();
            clientSocket->sendMessage(message);
        } else {
            break;
        }
    }

    delete clientSocket;

    return 0;
}