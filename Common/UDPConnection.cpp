#include "UDPConnection.hpp"

UDPConnection::UDPConnection(int sourcePort, int destinationPort)
    : m_srcConfig(sourcePort)
    , m_dstConfig(destinationPort)
    , m_sockfd(-1)
{
    // Initialize the socket here if needed
    m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
}

int UDPConnection::readDatagram(std::array<char, BUFFER_SIZE>& buffer)
{
    socklen_t len = sizeof(m_dstConfig.getAddress());

    // Receive messages from the client
    int n = recvfrom(m_sockfd, buffer.data(), buffer.size(), MSG_DONTWAIT,
        (struct sockaddr*)&m_dstConfig.getAddress(), &len);

    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            return 0; // Indicate no data received
        }
        std::cerr << "Error receiving message." << std::endl;
        return -1; // Real error
    }
    std::cout << n << " bytes received." << std::endl;
    // if (n < 0) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Avoid busy waiting
    //     continue; // No message received, continue to wait
    // }
    std::cout << "Received message: " << std::string(buffer.data(), n) << std::endl;

    return n;
}

int UDPConnection::writeDatagram(const std::array<char, BUFFER_SIZE>& buffer)
{
    if (buffer.empty()) {
        return 0; // No data to write
    }

    int n = sendto(m_sockfd, buffer.data(), buffer.size(),
        0, (const struct sockaddr*)&m_dstConfig.getAddress(), sizeof(m_dstConfig.getAddress()));

    if (n < 0) {
        std::cerr << "Error sending message." << std::endl;
    } else {
        std::cout << "Message send to target." << std::endl;
    }
    return n;
}
