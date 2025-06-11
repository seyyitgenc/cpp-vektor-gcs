#pragma once

#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <fcntl.h>
#include <functional>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>

#include "Constants.hpp"

class UDPClient {
public:
    UDPClient(int port)
        : m_port(port)
    {
        memset(&m_clientaddr, 0, sizeof(m_clientaddr));
        m_clientaddr.sin_family = AF_INET;
        m_clientaddr.sin_port = htons(port);
        m_clientaddr.sin_addr.s_addr = INADDR_ANY;
    }

    sockaddr_in& getAddress()
    {
        return m_clientaddr;
    }

    void setAddress(const sockaddr_in& addr)
    {
        m_clientaddr = addr;
    }

private:
    struct sockaddr_in m_clientaddr;
    int m_port;
};

class UDPServer {
public:
    UDPServer(int port)
        : m_port(port)
    {
        memset(&m_serveraddr, 0, sizeof(m_serveraddr));
        m_serveraddr.sin_family = AF_INET;
        m_serveraddr.sin_port = htons(port);
        m_serveraddr.sin_addr.s_addr = INADDR_ANY;
    }

    sockaddr_in& getAddress()
    {
        return m_serveraddr;
    }

    void setAddress(const sockaddr_in& addr)
    {
        m_serveraddr = addr;
    }

private:
    struct sockaddr_in m_serveraddr;
    int m_port;
};

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
        if (bind(m_sockfd, (const struct sockaddr*)&m_client.getAddress(), sizeof(m_client.getAddress())) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
    }

    int readDatagram(std::array<char, BUFFER_SIZE>& buffer);

    // Method to write a datagram to the socket
    int writeDatagram(const std::array<char, BUFFER_SIZE>& buffer);

private:
    UDPClient m_client;
    UDPServer m_server;
    int m_sockfd;
    char m_buffer[BUFFER_SIZE];
};
