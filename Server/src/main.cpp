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
    std::thread sendThread([&]() {
        while (true) {
            std::string message = std::format("Hello from server at {}", std::chrono::system_clock::now().time_since_epoch().count());
            std::array<char, 255> buffer {};
            std::copy(message.begin(), message.begin() + std::min(message.size(), static_cast<size_t>(255 - 1)), buffer.begin());
            int n = connection.writeDatagram(buffer);
            if (n > 0) {
            }

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