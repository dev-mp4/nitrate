#include "handshakepacket.hpp"

void HandshakePacket::parse(Packet& packet) {
    version = packet.readVarInt();
    address = packet.readString();
    port = packet.readUnsignedShort();
    intent = packet.readVarInt();
}