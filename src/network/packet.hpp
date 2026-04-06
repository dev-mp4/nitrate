#ifndef NITRATE_PACKET_HPP
#define NITRATE_PACKET_HPP

#include <string>
#include <cstdint>
#include <vector>
#include <network/network.hpp>

struct Packet {
    Packet();
    ~Packet();

    int length;
    int id;
    std::vector<uint8_t> payload;

    static Packet recv(Network& network, int socket);
    static void send(Network& network, int socket, std::vector<uint8_t> payload);

    int readVarInt();
    std::string readString();
    unsigned short readUnsignedShort();
    long long readLong();

private:
    size_t offset;
};

#endif // NITRATE_PACKET_HPP