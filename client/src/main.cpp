#if 1

#include "Constants.hpp"
#include "GUI/ImGuiEngine.hpp"
#include "GUI/MessageInfoGUI.hpp"
#include "GUI/RecieverTestGUI.hpp"
#include "GUI/SettingsGUI.hpp"
#include "GUI/TransmitterTestGUI.hpp"
#include "Globals.hpp"

#include "SocketListener.hpp"

namespace {

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

} // namespace

// Main code
auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> int
{

    SocketListener socketListener;
    socketListener.setupPort(8081);

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    gWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME, nullptr, nullptr);
    if (gWindow == nullptr)
        return -1;

    glfwMakeContextCurrent(gWindow);
    glfwSwapInterval(1); // Enable vsync

    ImGuiEngine engine(gWindow);
    engine.init();
    engine.addPanel("Reciever Test", std::make_unique<RecieverTestGUI>());
    engine.addPanel("Transmitter Test", std::make_unique<TransmitterTestGUI>());
    engine.addPanel("Message Info", std::make_unique<MessageInfoGUI>());
    engine.addPanel("Settings", std::make_unique<SettingsGUI>());

    while (!glfwWindowShouldClose(gWindow)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(gWindow, GLFW_ICONIFIED) != 0) {
            continue;
        }
        engine.render();
        glfwSwapBuffers(gWindow);
    }
    engine.shutdown();

    return 0;
}

#else

// Client side implementation of UDP client-server model
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    const char* hello = "Hello from client";
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len;

    // fcntl(sockfd, F_SETFL, O_NONBLOCK); // Set the socket to non-blocking mode
    sendto(sockfd, (const char*)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr*)&servaddr, sizeof(servaddr));

    while (true) {
        n = recvfrom(sockfd, (char*)buffer, MAXLINE, MSG_DONTWAIT, (struct sockaddr*)&servaddr, &len);
        if (n < 0) {
            continue; // Continue to wait for a message
        }
        buffer[n] = '\0';
        std::cout << "Server :" << buffer << std::endl;
    }

    close(sockfd);
    return 0;
}

#endif