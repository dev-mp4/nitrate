#include "network.hpp"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstddef>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

Network::Network(int port) : port(port) {}
Network::~Network() {}

struct Socket {
    sockaddr_in socket;
};

bool Network::init() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        return false;
    }

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        WSACleanup();
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        closesocket(server);
        WSACleanup();
        return false;
    }

    return true;
}

bool Network::listen(int backlog) {
    if (::listen(server, backlog) == SOCKET_ERROR) {
        closesocket(server);
        WSACleanup();
        return false;
    }
    return true;
}

int Network::accept() {
    sockaddr_in client;
    int client_size = sizeof(client);

    SOCKET client_socket = ::accept(server, (sockaddr*)&client, &client_size);
    if (client_socket == INVALID_SOCKET) {
        return -1;
    }
    return client_socket;
}

int Network::recv(int socket, void* buffer, size_t size, int flags) {
    return ::recv(socket, (char*) buffer, size, flags);
}

void Network::send(int socket, void* data, size_t size, int flags) {
    ::send(socket, (const char*) data, size, flags);
}

void Network::close(int socket) {
    closesocket(socket);
}

void Network::close() {
    closesocket(server);
    WSACleanup();
}

bool Network::poll() {
    TIMEVAL timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    fd_set set;
    FD_ZERO(&set);
    FD_SET(server, &set);

    int count = select(0, &set, nullptr, nullptr, &timeout);

    return count > 0 && FD_ISSET(server, &set);
}