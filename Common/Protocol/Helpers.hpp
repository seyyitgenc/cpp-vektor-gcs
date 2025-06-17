#pragma once

#include <cstdint>

namespace vek {

inline void byteCopy2(char* src, const char* dst)
{
    src[0] = dst[0];
    src[1] = dst[1];
}

inline void byteCopy4(char* src, const char* dst)
{
    src[0] = dst[0];
    src[1] = dst[1];
    src[2] = dst[2];
    src[3] = dst[3];
}

inline void byteCopy8(char* src, const char* dst)
{
    src[0] = dst[0];
    src[1] = dst[1];
    src[2] = dst[2];
    src[3] = dst[3];
    src[4] = dst[4];
    src[5] = dst[5];
    src[6] = dst[6];
    src[7] = dst[7];
}
inline void putUInt8(char* buffer, int offset, const uint8_t& value)
{
    buffer[offset] = value;
}

inline void putUnt8(char* buffer, int offset, const int8_t& value)
{
    buffer[offset] = value;
}

inline void putUInt16(char* buffer, int offset, const uint16_t& value)
{
    byteCopy2(&buffer[offset], reinterpret_cast<const char*>(&value));
}

inline void putInt16(char* buffer, int offset, const int16_t& value)
{
    byteCopy2(&buffer[offset], reinterpret_cast<const char*>(&value));
}

inline void putUInt32(char* buffer, int offset, const uint32_t& value)
{
    byteCopy4(&buffer[offset], reinterpret_cast<const char*>(&value));
}

inline void putInt32(char* buffer, int offset, const int32_t& value)
{
    byteCopy4(&buffer[offset], reinterpret_cast<const char*>(&value));
}

inline void putFloat(char* buffer, int offset, const float& value)
{
    byteCopy4(&buffer[offset], reinterpret_cast<const char*>(&value));
}

inline void putUInt64(char* buffer, int offset, const uint64_t& value)
{
    byteCopy8(&buffer[offset], reinterpret_cast<const char*>(&value));
}

inline void putInt64(char* buffer, int offset, const int64_t& value)
{
    byteCopy8(&buffer[offset], reinterpret_cast<const char*>(&value));
}

template <typename T>
T readFromBuffer(const uint8_t* buffer, int offset)
{
    T value;
    std::memcpy(&value, buffer + offset, sizeof(T));
    return value;
}

} // namespace vek
