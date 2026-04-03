#include <iomanip>
#include <iostream>
#include "network/network.hpp"
#include "network/packet.hpp"
#include "packets/handshakepacket.hpp"
#include "packets/pingpacket.hpp"
#include "packets/statusresponsepacket.hpp"

void print_hex(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        std::cout << std::hex
                  << std::setfill('0')
                  << (static_cast<unsigned int>(static_cast<uint8_t>(data[i])))
                  << " ";
    }
    std::cout << std::endl;
}

int main() {
    StatusResponsePacket srp;
    srp.version = "1.16.5";
    srp.protocolVersion = 754;
    srp.maxPlayers = 1488;
    srp.onlinePlayers = 67;
    srp.motd = u8"хуй говно пизда залупа";

    Network network(25565);

    if (!network.init()) {
        std::cerr << "Failed to initialize network!" << std::endl;
        return 1;
    }

    network.listen(5);

    while (1) {
        int client = network.accept();

        Packet packet = Packet::recv(network, client);

        switch (packet.id) {
            case 0: {
                HandshakePacket handshake;
                handshake.parse(packet);

                if (handshake.intent == 1) {
                    Packet::send(network, client, srp.encode());
                }
            }

            case 1: {
                PingPacket ping;
                ping.parse(packet);

                Packet::send(network, client, ping.encode());
            }
        }

        
    }

    network.close();

    return 0;
}