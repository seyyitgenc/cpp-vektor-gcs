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

#include <memory>
#include <vector>

static constexpr int MAX_LINE = 1024;

class SocketListener {
public:
    using Callback = std::function<void(const char*)>;
    SocketListener();
    ~SocketListener();

    // Method to start listening on a socket
    void setupPort(int port);

    int readDatagram(char* buffer, int bufferSize);
    int writeDatagram(char* buffer, int bufferSize);

    void addCallback(std::unique_ptr<Callback> callback)
    {
        m_callbacks.push_back(std::move(callback));
    }

    void removeCallback(std::unique_ptr<Callback> callback)
    {
        m_callbacks.erase(std::remove(m_callbacks.begin(), m_callbacks.end(), callback), m_callbacks.end());
    }

    // Notify all registered listeners with a message
    void NotifyListeners(const char* message)
    {
        for (const auto& callback : m_callbacks) {
            (*callback)(message);
        }
    }

private:
    // Private members can be added here, such as socket descriptors, buffers, etc.
    int m_sockfd;
    char m_buffer[MAX_LINE];
    struct sockaddr_in servaddr;

    std::vector<std::unique_ptr<Callback>> m_callbacks;
};
