#ifndef NITRATE_CLIENT_HPP
#define NITRATE_CLIENT_HPP

#include <network/network.hpp>

enum class ClientState {
    HANDSHAKING,
    WAITING_FOR_SLP,
    PINGING
};

class Client {
public:
    Client(int fd, Network* network);
    ~Client();

    int fd;

    ClientState state;
    Network* network;

    bool shouldDisconnect;

    void update();
    void close();

private:
    void handleHandshake();
    void sendSLP();
    void respondPing();
};

#endif // NITRATE_CLIENT_HPP