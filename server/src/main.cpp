#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <format>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <thread>

int main(int argc, char* argv[])
{
    int sockfd;
    const char* hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Configure client address to send to (no need to receive first!)
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(8081); // Client listens on port 8081

    std::cout << "UDP Server starting to send messages to client on port 8081" << std::endl;

    std::thread sendThread([&]() {
        while (true) {
            // Send a message to the client
            int n = sendto(sockfd, (const char*)hello, strlen(hello),
                0, (const struct sockaddr*)&cliaddr, sizeof(cliaddr));

            if (n < 0) {
                std::cerr << "Error sending message." << std::endl;
            } else {
                std::cout << "Hello message sent to client." << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    sendThread.detach(); // Detach the thread to run independently

    std::thread listenerThread([&]() {
        char buffer[1024];
        socklen_t len = sizeof(servaddr);

        while (true) {
            // Receive messages from the client
            int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, MSG_DONTWAIT,
                (struct sockaddr*)&servaddr, &len);
            if (n < 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Avoid busy waiting
                continue; // No message received, continue to wait
            }

            buffer[n] = '\0'; // Null-terminate the received string
            std::cout << "Received message from client: " << buffer << std::endl;
        }
    });

    listenerThread.join(); // Detach the listener thread to run independently

    close(sockfd);
    return 0;
}