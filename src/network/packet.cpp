#include "packet.hpp"
#include <cstdint>
#include <util/util.hpp>
#include <vector>

Packet::Packet() : length(0), id(0), payload(), offset(0) {}
Packet::~Packet() {}

Packet Packet::recv(Network& network, int socket) {
    Packet packet;

    auto readVarIntFromSocket = [&](int& out) -> bool {
        int numRead = 0;
        int result = 0;
        uint8_t byte = 0;

        do {
            int n = network.recv(socket, &byte, 1, 0);
            if (n <= 0) return false;

            int value = byte & 0x7F;
            result |= (value << (7 * numRead));

            numRead++;
            if (numRead > 5) return false;

        } while (byte & 0x80);

        out = result;
        return true;
    };

    // Read packet length
    if (!readVarIntFromSocket(packet.length) || packet.length <= 0)
        return Packet();

    // Read full packet body
    std::vector<uint8_t> buffer(packet.length);
    size_t total = 0;

    while (total < buffer.size()) {
        int n = network.recv(socket, buffer.data() + total, buffer.size() - total, 0);
        if (n <= 0) return Packet();
        total += n;
    }

    // Parse packet ID
    size_t offset = 0;
    size_t idSize = 0;

    packet.id = Util::readVarInt(buffer.data(), offset, buffer.size(), &idSize);
    if (packet.id == -1) return Packet();

    offset += idSize;

    // Extract payload
    packet.payload.assign(buffer.begin() + offset, buffer.end());

    return packet;
}

void Packet::send(Network& network, int socket, std::vector<uint8_t> payload) {
    std::vector<uint8_t> length = Util::encodeVarInt(payload.size());
    std::vector<uint8_t> bytes;
    bytes.reserve(length.size() + payload.size());
    bytes.insert(bytes.end(), length.begin(), length.end());
    bytes.insert(bytes.end(), payload.begin(), payload.end());
    network.send(socket, bytes.data(), bytes.size(), 0);
}

int Packet::readVarInt() {
    size_t size = 0;
    int result = Util::readVarInt(payload.data(), offset, payload.size(), &size);
    offset += size;
    return result;
}

std::string Packet::readString() {
    int length = readVarInt();
    const char* cstr = (const char*) payload.data() + offset;
    std::string str(cstr, length);
    offset += length;
    return str;
}

unsigned short Packet::readUnsignedShort() {
    if (offset + 2 > payload.size())
        return 0;

    uint16_t value =
        (payload[offset] << 8) |
        (payload[offset + 1]);

    offset += 2;
    return value;
}

long long Packet::readLong() {
    if (offset + 8 > payload.size()) return 0;

    int64_t value =
        (int64_t(payload[offset])     << 56) |
        (int64_t(payload[offset + 1]) << 48) |
        (int64_t(payload[offset + 2]) << 40) |
        (int64_t(payload[offset + 3]) << 32) |
        (int64_t(payload[offset + 4]) << 24) |
        (int64_t(payload[offset + 5]) << 16) |
        (int64_t(payload[offset + 6]) << 8)  |
        (int64_t(payload[offset + 7]));

    offset += 8;
    return value;
}