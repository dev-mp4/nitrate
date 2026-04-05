#include "server.hpp"
#include <iostream>

Server* Server::instance;

Server::Server(Network& network) : network(network) {
    instance = this;
}

Server::~Server() {
    instance = nullptr;
}

Server* Server::getInstance() {
    return instance;
}

bool Server::init() {
    if (!network.init()) {
        return false;
    }
    return true;
}

void Server::close() {
    isRunning = false;
}

void Server::run() {
    network.listen(5);

    isRunning = true;

    while (isRunning) {
        if (network.poll()) {
            int client_fd = network.accept();
            clients.emplace_back(client_fd, &network);
        }

        for (auto it = clients.begin(); it != clients.end(); ) {
            it->update();

            if (it->shouldDisconnect) {
                it = clients.erase(it); // safe
            } else {
                ++it;
            }
        }
    }

    network.close();
}