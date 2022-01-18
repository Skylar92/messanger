#undef UNICODE

#include <functional>

#include "../../core/socket/SocketConnector.h"
#include "../../core/socket/dto/Message.h"
#include "../../core/socket/utils/SerializationUtils.h"

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFFER 4096
#define DEFAULT_PORT "27015"

class ClientSocketConnector : protected SocketConnector {
public:

    ClientSocketConnector(string username): SocketConnector(), username(move(username)) {};

    ~ClientSocketConnector();

    void setupConnection();

    void sendMessage(const char *message);

    void listening(const std::function<void(std::string)>& callback);

private:

    string username;
    SOCKET connectSocket = INVALID_SOCKET;

    struct addrinfo
            *result = NULL,
            *ptr = NULL,
            hints{};

};
