#ifndef NITRATE_STATUSRESPONSEPACKET_HPP
#define NITRATE_STATUSRESPONSEPACKET_HPP

#include <packets/ispacket.hpp>
#include <cstdint>

struct StatusResponsePacket : public ISPacket {
    std::string version;
    int protocolVersion;
    int maxPlayers;
    int onlinePlayers;
    std::string motd;

    std::vector<uint8_t> encode() override;
};

#endif // NITRATE_STATUSRESPONSEPACKET_HPP