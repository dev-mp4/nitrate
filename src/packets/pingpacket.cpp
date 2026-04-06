#include "pingpacket.hpp"
#include <util/util.hpp>
#include <vector>
#include <cstdint>

void PingPacket::parse(Packet& packet) {
    number = packet.readLong();
}

std::vector<uint8_t> PingPacket::encode() {
    std::vector<uint8_t> bytes;
    std::vector<uint8_t> numberBytes = Util::encodeLong(number);
    std::vector<uint8_t> id = Util::encodeVarInt(1);
    bytes.reserve(numberBytes.size() + id.size());
    bytes.insert(bytes.end(), id.begin(), id.end());
    bytes.insert(bytes.end(), numberBytes.begin(), numberBytes.end());
    return bytes;
}