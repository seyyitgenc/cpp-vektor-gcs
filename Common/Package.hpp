#pragma once

#include <cstdint>

#include "Common/Protocol/Helpers.hpp"

namespace vek {

static constexpr u_int8_t PACKAGE_MAGIC = 0xAF; // Magic number to identify the Package type
static constexpr u_int8_t PAYLOAD_SIZE = 255; // Maximum size of the payload payload

struct Package {
    uint8_t magic; // Magic number to identify the Package type
    uint8_t size; // Size of the Package payload
    uint8_t seq; // Sequence number
    uint32_t messageId; // Unique identifier for the message
    uint8_t payload[PAYLOAD_SIZE]; // Data payload,
    uint16_t checksum; // Checksum for error detection
};

void packageToSendBuffer(const Package& package, char* buffer)
{
    buffer[0] = package.magic;
    buffer[1] = package.size;
    buffer[2] = package.seq;
    buffer[3] = package.messageId & 0xFF;
    buffer[4] = (package.messageId >> 8) & 0xFF;
    buffer[5] = (package.messageId >> 16) & 0xFF;
    memcpy(&buffer[6], package.payload, package.size);
}

inline Package gParseBuffer {};

static int state = 0;
static int packageIdx = 0;
int parseChar(char c, Package* outPackage)
{
    // std::cout << "test " << (int)c << std::endl;

    // TODO: later on implement some kind of state machine
    switch (state) {
    case 0: // which means idle/uninit
        if (static_cast<u_int8_t>(c) == PACKAGE_MAGIC) {
            state = 1;
            gParseBuffer.magic = static_cast<uint8_t>(c);
        } else {
            return 0;
        }
        break;
    case 1: // size
        gParseBuffer.size = static_cast<uint8_t>(c);
        state = 2;
        break;
    case 2: // sequence
        gParseBuffer.seq = static_cast<uint8_t>(c);
        state = 3;
        break;
    case 3: // msg lower bit
        gParseBuffer.messageId |= (static_cast<uint32_t>(c) & 0xFF);
        state = 4;
        break;
    case 4: // msg mid bit
        gParseBuffer.messageId |= ((static_cast<uint32_t>(c) << 8) & 0x00FF00);
        state = 5;
        break;
    case 5: // msg high bit
        gParseBuffer.messageId |= ((static_cast<uint32_t>(c) << 16) & 0xFF0000);
        state = 6;
        break;
    case 6: // payload
        if (packageIdx < gParseBuffer.size) {
            gParseBuffer.payload[packageIdx++] = c;
        } else {
            state = 7;
        }
        break;
    case 7: // package parsed succesfully
        packageIdx = 0;
        *outPackage = gParseBuffer;
        return 1; // success
        break;

    default:
        break;
    }
    return 0;
}
} // namespace vek