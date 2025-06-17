#pragma once

#include <cstdint>

#include "Common/Protocol/Helpers.hpp"

namespace vek {

static constexpr int PACKET_MAGIC = 0xAF; // Magic number to identify the packet type

static constexpr int PAYLOAD_SIZE = 256; // Maximum size of the payload payload

static constexpr int GPS_MESSAGE_ID = 0x01; // Unique identifier for GPS messages
static constexpr int GPS_PACK_SIZE = 00;

struct Packet {
    uint8_t magic; // Magic number to identify the packet type
    uint8_t size; // Size of the packet payload
    uint8_t seq; // Sequence number
    uint32_t messageId; // Unique identifier for the message
    uint8_t payload[PAYLOAD_SIZE]; // Data payload,
    uint16_t checksum; // Checksum for error detection
};

struct GPSPacket {
    uint64_t timestamp = 0; // Timestamp in microseconds since epoch
    uint64_t latitude = 0; // Latitude in degrees need to divide int64_t by 1e7 for actual value
    uint64_t longitude = 0; // Longitude in degrees need to divide int64_t by 1e7 for actual value
    float altitude = 0; // Altitude in meters
    float speed = 0; // Speed in meters per second
    float heading = 0; // Heading in degrees
};

int packGPSPacket(const GPSPacket& gpsPacket, Packet& outPacket)
{
    outPacket.magic = PACKET_MAGIC;
    // outPacket.size = sizeof(GPSPacket);
    outPacket.messageId = GPS_MESSAGE_ID;
    outPacket.seq++; // Increment sequence number
    outPacket.checksum = 0; // calc checksum here
    outPacket.size = GPS_PACK_SIZE;

    char buffer[PAYLOAD_SIZE];
    putUInt64(buffer, 0, gpsPacket.timestamp);
    putUInt64(buffer, 8, gpsPacket.latitude);
    putUInt64(buffer, 16, gpsPacket.longitude);
    putUInt64(buffer, 24, gpsPacket.altitude);
    putFloat(buffer, 32, gpsPacket.speed);
    putFloat(buffer, 36, gpsPacket.heading);

    memcpy(outPacket.payload, buffer, 40);

    return 0; // Placeholder return value
}

// Usage in your decode function:
int encodeGPSPack(const Packet& packet, GPSPacket& outPack)
{
    outPack.timestamp = readFromBuffer<uint64_t>(packet.payload, 0);
    outPack.latitude = readFromBuffer<uint64_t>(packet.payload, 8);
    outPack.longitude = readFromBuffer<uint64_t>(packet.payload, 16);
    outPack.altitude = readFromBuffer<uint64_t>(packet.payload, 24);
    outPack.speed = readFromBuffer<float>(packet.payload, 32);
    outPack.heading = readFromBuffer<float>(packet.payload, 36);
    return 0;
}

} // namespace vek