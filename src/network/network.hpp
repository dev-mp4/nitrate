#ifndef NITRATE_NETWORK_HPP
#define NITRATE_NETWORK_HPP

#include <cstddef>

class Network {
public:
    Network(int port);
    ~Network();

    bool init();
    bool listen(int backlog);
    int accept();
    int recv(int socket, void* buffer, size_t size, int flags);
    void send(int socket, void* data, size_t size, int flags);
    void close(int socket);
    void close();

private:
    int port;
    int server;
};

#endif // NITRATE_NETWORK_HPP