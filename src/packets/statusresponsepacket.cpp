#include "statusresponsepacket.hpp"
#include <cstdint>
#include <sstream>
#include <util/util.hpp>
#include <vector>

std::vector<uint8_t> StatusResponsePacket::encode() {
    std::vector<uint8_t> bytes;

    std::ostringstream oss;
    oss << u8"{\"version\":{\"name\":\"" << version << u8"\",\"protocol\":" << protocolVersion << u8"}"
        << u8",\"players\":{\"max\":" << maxPlayers << u8",\"online\":" << onlinePlayers << u8"}"
        << u8",\"description\":{\"text\":\"" << motd << u8"\"}"
        << u8",\"enforcesSecureChat\":false}";

    std::vector<uint8_t> id = Util::encodeVarInt(0);
    std::vector<uint8_t> responseBytes = Util::encodeString(oss.str());

    bytes.reserve(id.size() + responseBytes.size());
    bytes.insert(bytes.end(), id.begin(), id.end());
    bytes.insert(bytes.end(), responseBytes.begin(), responseBytes.end());

    return bytes;
}