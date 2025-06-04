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

    n = recvfrom(m_sockfd, (char*)m_buffer, bufferSize,
        MSG_DONTWAIT, (struct sockaddr*)&servaddr,
        &len);

    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            // No data available, sleep briefly to avoid busy waiting
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            return 0; // Indicate no data received
        }
        return -1; // Real error
    }
    std::cout << "Server :" << m_buffer << std::endl;
    return n;
}

int SocketListener::writeDatagram(char* buffer)
{
    return sendto(m_sockfd, (const char*)buffer, sizeof(buffer),
        MSG_CONFIRM, (const struct sockaddr*)&servaddr,
        sizeof(servaddr));
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

        while (true) {
            readDatagram(buffer, sizeof(buffer));
        }
    });

    listenerThread.detach();
}
