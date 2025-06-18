#pragma once

#include <cstdint>

#include "Common/Protocol/Helpers.hpp"

namespace vek {

static constexpr int PACKAGE_MAGIC = 0xAF; // Magic number to identify the Package type
static constexpr int PAYLOAD_SIZE = 256; // Maximum size of the payload payload

struct Package {
    uint8_t magic; // Magic number to identify the Package type
    uint8_t size; // Size of the Package payload
    uint8_t seq; // Sequence number
    uint32_t messageId : 24; // Unique identifier for the message
    uint8_t payload[PAYLOAD_SIZE]; // Data payload,
    uint16_t checksum; // Checksum for error detection
};

void packageToSendBuffer(const Package& package, char* buffer)
{
    buffer[0] = package.magic;
    buffer[1] = package.size;
    buffer[2] = package.seq;
    buffer[3] = package.messageId && 0xFF;
    buffer[4] = (package.messageId >> 8) & 0xFF;
    buffer[5] = (package.messageId >> 8) & 0xFF;
    memcpy(&buffer[6], package.payload, package.size);
}

inline Package gParseBuffer {};

int parseChar(char c, Package& outPackage)
{
    // TODO: later on implement some kind of state machine
    static int state = 0;

    switch (state) {
    case 0: // which means idle/uninit
        if (c == PACKAGE_MAGIC) {
            state = 1;
            gParseBuffer.magic = c;
        } else {
            return -1;
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
    case 3: // sequence
        gParseBuffer.messageId = static_cast<uint8_t>(c);
        state = 4;
        break;
    default:
        break;
    }
    return -1;
}
} // namespace vek