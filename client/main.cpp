#include "socket/ClientSocketConnector.h"
#include <string>
#include <iostream>
#include <thread>

void listening(ClientSocketConnector *clientSocket) {
    clientSocket->listening(
            [](const Message &message) -> void { printf("%s: %s", message.username.c_str(), message.text.c_str()); });
}

int main() {

    string username;

    printf("Enter your name: ");
    cin >> username;

    auto *clientSocket = new ClientSocketConnector(username);
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