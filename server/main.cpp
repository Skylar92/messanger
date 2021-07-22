#undef UNICODE

#include "socket/TCPServer.h"

int main() {
    auto server = TCPServer();
    server.startServer();
    return 0;
}

