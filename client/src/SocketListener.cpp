#include "SocketListener.hpp"
#include "Constants.hpp"

SocketListener::SocketListener()
{
}

SocketListener::~SocketListener()
{
    close(m_sockfd);
    std::cout << "Socket closed." << std::endl;
}

int SocketListener::readDatagram(char* m_buffer, int bufferSize)
{
    int n;
    socklen_t len;

    std::cout << "Waiting for a message" << std::endl;
    n = recvfrom(m_sockfd, (char*)m_buffer, bufferSize,
        MSG_DONTWAIT, (struct sockaddr*)&servaddr,
        &len);

    if (n < 0) {
        return -1; // Return -1 on error
    }

    m_buffer[n] = '\0';
    std::cout << "Server :" << m_buffer << std::endl;
}

int SocketListener::writeDatagram(char* buffer, int bufferSize)
{
    const char* hello = "Hello from client";
    sendto(m_sockfd, (const char*)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr*)&servaddr,
        sizeof(servaddr));
    std::cout << "Hello message sent." << std::endl;
}

void SocketListener::setupPort(int port)
{
    // Creating UDP socket
    if ((m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // THIS IS WHAT YOU'RE MISSING - BIND THE CLIENT!
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(port); // Client listens on this port
    clientaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind to receive messages
    if (bind(m_sockfd, (const struct sockaddr*)&clientaddr, sizeof(clientaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "UDP Client listening on port " << port << std::endl;

    // Server info (for sending only, not receiving)
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);

    // NO NEED TO SEND ANYTHING - just start listening!
    std::thread listenerThread([this]() {
        char buffer[1024];
        int n;

        while (true) {
            n = recvfrom(m_sockfd, buffer, 1024, 0, nullptr, nullptr);
            if (n > 0) {
                buffer[n] = '\0';
                std::cout << "Received: " << buffer << std::endl;
                NotifyListeners(buffer);
            }
            sendto(m_sockfd, buffer, n, 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
        }
    });

    listenerThread.detach();
}
