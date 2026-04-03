#ifndef NITRATE_ICPACKET_HPP
#define NITRATE_ICPACKET_HPP

#include <network/packet.hpp>

struct ICPacket {
    virtual ~ICPacket() = default;
    virtual void parse(Packet& packet) = 0;
};

#endif // NITRATE_ICPACKET_HPP