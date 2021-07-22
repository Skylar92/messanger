#undef UNICODE

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include <functional>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFFER 4096
#define DEFAULT_PORT "27015"

class ClientSocketConnector {
public:

    ~ClientSocketConnector();

    void setupConnection();

    void sendMessage(const char *message);

    void listening( std::function<void(std::string)> callback );

private:

    SOCKET ClientSocket = INVALID_SOCKET;
    SOCKET ConnectSocket = INVALID_SOCKET;

    int iResult;

    struct addrinfo
            *result = NULL,
            *ptr = NULL,
            hints{};

};
