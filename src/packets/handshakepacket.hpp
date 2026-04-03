#ifndef NITRATE_HANDSHAKEPACKET_HPP
#define NITRATE_HANDSHAKEPACKET_HPP

#include <packets/icpacket.hpp>

struct HandshakePacket : public ICPacket {
    int version;
    std::string address;
    unsigned short port;
    int intent;

    void parse(Packet& packet) override;
};

#endif // NITRATE_HANDSHAKEPACKET_HPP