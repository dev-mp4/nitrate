#ifndef NITRATE_UTIL_HPP
#define NITRATE_UTIL_HPP

#include <vector>
#include <string>

namespace Util {
    int readVarInt(const uint8_t* data, size_t offset, size_t size, size_t* out_size);
    std::vector<uint8_t> encodeVarInt(int value);
    std::vector<uint8_t> encodeString(std::string value);
    std::vector<uint8_t> encodeLong(int64_t value);
};

#endif // NITRATE_UTIL_HPP