#ifdef __linux__

#include "network.hpp"
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

Network::Network(int port) : port(port) {}
Network::~Network() {}

bool Network::init() {
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == -1) {
        return false;
    }

    struct sockaddr_in address {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server, (struct sockaddr*)&address, sizeof(address)) < 0) {
        return false;
    }

    return true;
}

bool Network::listen(int backlog) {
    if (::listen(server, backlog) < 0) {
        close(server);
        return false;
    }
    return true;
}

int Network::accept() {
    sockaddr_in client;
    socklen_t client_size = sizeof(client);

    int client_socket = ::accept(server, (sockaddr*)&client, &client_size);
    return client_socket;
}

int Network::recv(int socket, void* buffer, size_t size, int flags) {
    return ::recv(socket, (char*) buffer, size, flags);
}

void Network::send(int socket, void* data, size_t size, int flags) {
    ::send(socket, (const char*) data, size, flags);
}

void Network::close(int socket) {
    ::close(socket);
}

void Network::close() {
    ::close(server);
}

bool Network::poll() {
    fd_set set;
    struct timeval timeout;

    FD_ZERO(&set);
    FD_SET(server, &set);

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    int count = select(server + 1, &set, nullptr, nullptr, &timeout);

    return count > 0 && FD_ISSET(server, &set);
}

#endif