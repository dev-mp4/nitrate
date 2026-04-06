#include "util.hpp"
#include <cstdint>

int Util::readVarInt(const uint8_t* data, size_t offset, size_t size, size_t* out_size) {
    int numRead = 0;
    int result = 0;
    uint8_t read;
    do {
        if (offset >= size) return -1;
        read = data[offset++];
        int value = read & 0b01111111;
        result |= (value << (7 * numRead));
        numRead++;
        if (numRead > 5) return -1;
    } while (read & 0b10000000);

    if (out_size != nullptr) {
        *out_size = numRead;
    }

    return result;
}

std::vector<uint8_t> Util::encodeVarInt(int value) {
    std::vector<uint8_t> bytes;
    do {
        uint8_t temp = value & 0x7F;
        value >>= 7;
        if (value != 0) temp |= 0x80;  // more bytes follow
        bytes.push_back(temp);
    } while (value != 0);
    return bytes;
}

std::vector<uint8_t> Util::encodeString(std::string value) {
    std::vector<uint8_t> bytes;
    std::vector<uint8_t> length = Util::encodeVarInt((int) value.size());
    bytes.reserve(length.size() + value.size());
    bytes.insert(bytes.end(), length.begin(), length.end());
    bytes.insert(bytes.end(), value.begin(), value.end());
    return bytes;
}

std::vector<uint8_t> Util::encodeLong(int64_t value) {
    std::vector<uint8_t> bytes(8);

    bytes[0] = (value >> 56) & 0xFF;
    bytes[1] = (value >> 48) & 0xFF;
    bytes[2] = (value >> 40) & 0xFF;
    bytes[3] = (value >> 32) & 0xFF;
    bytes[4] = (value >> 24) & 0xFF;
    bytes[5] = (value >> 16) & 0xFF;
    bytes[6] = (value >> 8)  & 0xFF;
    bytes[7] = value & 0xFF;

    return bytes;
}