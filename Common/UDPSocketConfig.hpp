#pragma once

#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <stdlib.h>

class UDPSocketConfig {
public:
    UDPSocketConfig(int port)
        : m_port(port)
    {
        memset(&m_addr, 0, sizeof(m_addr));
        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(port);
        m_addr.sin_addr.s_addr = INADDR_ANY;
    }

    sockaddr_in& getAddress()
    {
        return m_addr;
    }

    void setAddress(const sockaddr_in& addr)
    {
        m_addr = addr;
    }

private:
    struct sockaddr_in m_addr;
    int m_port;
};
