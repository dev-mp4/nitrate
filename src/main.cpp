#include "network/network.hpp"
#include <server/server.hpp>

int main() {
    Network network(25565);

    Server server(network);
    server.version = "1.16.5";
    server.protocolVersion = 754;
    server.maxPlayers = 10;
    server.motd = u8"Nitrate server";

    server.init();

    server.run();

    return 0;
}