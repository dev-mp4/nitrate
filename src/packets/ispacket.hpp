#ifndef NITRATE_ISPACKET_HPP
#define NITRATE_ISPACKET_HPP

#include <cstdint>
#include <network/packet.hpp>
#include <vector>

struct ISPacket {
    virtual ~ISPacket() = default;
    virtual std::vector<uint8_t> encode() = 0;
};

#endif // NITRATE_ISPACKET_HPP