#pragma once

#include "Constants.hpp"
#include "UDPSocketConfig.hpp"

#include <array>

class UDPConnection {
public: // Method to read a datagram from the socket
    UDPConnection(int sourcePort, int destinationPort);
    ~UDPConnection()
    {
        if (m_sockfd != -1) {
            close(m_sockfd);
        }
        m_sockfd = -1;
        memset(m_buffer, 0, sizeof(m_buffer));
    }

    void bindSocket()
    {
        // Bind the socket to the client address
        if (bind(m_sockfd, (const struct sockaddr*)&m_srcConfig.getAddress(), sizeof(m_srcConfig.getAddress())) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
    }

    int readDatagram(std::array<char, BUFFER_SIZE>& buffer);

    // Method to write a datagram to the socket
    int writeDatagram(const std::array<char, BUFFER_SIZE>& buffer);

private:
    UDPSocketConfig m_srcConfig;
    UDPSocketConfig m_dstConfig;

    int m_sockfd;
    char m_buffer[BUFFER_SIZE];
};
