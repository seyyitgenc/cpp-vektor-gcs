#pragma once

#include "../Package.hpp"

namespace vek {

static constexpr int GPS_MESSAGE_ID = 0x01; // Unique identifier for GPS messages
static constexpr int GPS_PACK_SIZE = 31;

struct GPSPackage {
    uint64_t timestamp = 0; // Timestamp in microseconds since epoch
    uint64_t latitude = 0; // Latitude in degrees need to divide int64_t by 1e7 for actual value
    uint64_t longitude = 0; // Longitude in degrees need to divide int64_t by 1e7 for actual value
    float altitude = 0; // Altitude in meters
    float speed = 0; // Speed in meters per second
    float heading = 0; // Heading in degrees
};

int encodeGPSPackage(const GPSPackage& gpsPackage, Package& outPackage)
{
    outPackage.magic = PACKAGE_MAGIC;
    // outPackage.size = sizeof(GPSPackage);
    outPackage.messageId = GPS_MESSAGE_ID;
    outPackage.seq++; // Increment sequence number
    outPackage.checksum = 0; // calc checksum here
    outPackage.size = GPS_PACK_SIZE;

    char buffer[PAYLOAD_SIZE];
    putUInt64(buffer, 0, gpsPackage.timestamp);
    putUInt64(buffer, 8, gpsPackage.latitude);
    putUInt64(buffer, 16, gpsPackage.longitude);
    putUInt64(buffer, 24, gpsPackage.altitude);
    putFloat(buffer, 32, gpsPackage.speed);
    putFloat(buffer, 36, gpsPackage.heading);

    memcpy(outPackage.payload, buffer, 40);

    return 0; // Placeholder return value
}

// Usage in your decode function:
int decodeGPSPackage(const Package& package, GPSPackage& outPack)
{
    outPack.timestamp = readFromBuffer<uint64_t>(package.payload, 0);
    outPack.latitude = readFromBuffer<uint64_t>(package.payload, 8);
    outPack.longitude = readFromBuffer<uint64_t>(package.payload, 16);
    outPack.altitude = readFromBuffer<uint64_t>(package.payload, 24);
    outPack.speed = readFromBuffer<float>(package.payload, 32);
    outPack.heading = readFromBuffer<float>(package.payload, 36);
    return 0;
}

} // namespace vek
