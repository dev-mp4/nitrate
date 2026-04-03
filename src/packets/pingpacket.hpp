#ifndef NITRATE_PINGPACKET_HPP
#define NITRATE_PINGPACKET_HPP

#include <cstdint>
#include <network/packet.hpp>
#include <packets/icpacket.hpp>
#include <packets/ispacket.hpp>

struct PingPacket : public ICPacket, public ISPacket {
    long long number;

    void parse(Packet& packet) override;
    std::vector<uint8_t> encode() override;
};

#endif // NITRATE_PINGPACKET_HPP