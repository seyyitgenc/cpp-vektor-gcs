#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <format>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <thread>

#include "Common/Package.hpp"
#include "Common/Packages/GPSPackage.hpp"
#include "Common/UDPConnection.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    UDPConnection connection(8080, 8081);
    connection.bindSocket();

    vek::GPSPackage gpsPack {
        .timestamp = 1212323,
        .latitude = 333,
        .longitude = 444,
        .altitude = 313131,
        .speed = 2,
        .heading = 330,
    };

    vek::Package outPack {};
    vek::encodeGPSPackage(gpsPack, outPack);
    if (outPack.messageId == vek::GPS_MESSAGE_ID) {
        vek::GPSPackage decodedGPSPack;
        vek::decodeGPSPackage(outPack, decodedGPSPack);
        std::cout << decodedGPSPack.timestamp << std::endl;
        std::cout << decodedGPSPack.latitude << std::endl;
        std::cout << decodedGPSPack.longitude << std::endl;
        std::cout << decodedGPSPack.altitude << std::endl;
        std::cout << decodedGPSPack.speed << std::endl;
        std::cout << decodedGPSPack.heading << std::endl;
    } else {
        std::cout << "Message is something else" << std::endl;
    }

    std::thread sendThread([&]() {
        while (true) {
            std::array<char, 255> buffer;
            packageToSendBuffer(outPack, buffer.data());

            [[maybe_unused]] int n = connection.writeDatagram(buffer);

            // // Send a message to the client
            // int n = sendto(sockfd, (const char*)hello, strlen(hello),
            //     0, (const struct sockaddr*)&cliaddr, sizeof(cliaddr));
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    sendThread.detach(); // Detach the thread to run independently

    std::thread listenerThread([&]() {
        std::array<char, 255> buffer;
        while (true) {
            int n = connection.readDatagram(buffer);
            if (n > 0) {
                uint64_t value = 0;
                value = vek::readFromBuffer<uint8_t>((uint8_t*)buffer.data(), 1);
                std::cout << "Received message: " << value << std::endl;
            }

            if (n < 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Avoid busy waiting
                continue; // No message received, continue to wait
            }
        }
    });

    listenerThread.join(); // Detach the listener thread to run independently

    return 0;
}