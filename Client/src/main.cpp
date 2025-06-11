#include "GUI/ImGuiEngine.hpp"
#include "GUI/MessageInfoGUI.hpp"
#include "GUI/RecieverTestGUI.hpp"
#include "GUI/SettingsGUI.hpp"
#include "GUI/TransmitterTestGUI.hpp"
#include "Globals.hpp"

#include "Common/Constants.hpp"
#include "Common/UDPConnection.hpp"

namespace {

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

} // namespace

// Main code
auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> int
{
    UDPConnection connection(8081, 8080);
    connection.bindSocket();
    std::thread sendThread([&]() {
        while (true) {
            std::string message = std::format("Hello from client at {}", std::chrono::system_clock::now().time_since_epoch().count());
            std::array<char, BUFFER_SIZE> buffer {};
            std::copy(message.begin(), message.begin() + std::min(message.size(), static_cast<size_t>(BUFFER_SIZE - 1)), buffer.begin());
            // int n = connection.writeDatagram(buffer);

            // if (n < 0) {
            //     std::cerr << "Error sending message." << std::endl;
            // } else {
            //     std::cout << "Message sent to server" << std::endl;
            // }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    sendThread.detach(); // Detach the thread to run independently

    std::thread listenerThread([&]() {
        std::array<char, BUFFER_SIZE> buffer;
        while (true) {
            int n = connection.readDatagram(buffer);

            if (n < 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Avoid busy waiting
                continue; // No message received, continue to wait
            }
        }
    });
    listenerThread.detach(); // Detach the listener thread to run independently

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