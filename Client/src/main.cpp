#include "GUI/ImGuiEngine.hpp"
#include "GUI/MessageInfoGUI.hpp"
#include "GUI/RecieverTestGUI.hpp"
#include "GUI/SettingsGUI.hpp"
#include "GUI/TransmitterTestGUI.hpp"
#include "Globals.hpp"

#include "Common/Constants.hpp"
#include "Common/UDPConnection.hpp"

#include "Common/Package.hpp"
#include "Common/Packages/GPSPackage.hpp"

namespace {

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

} // namespace

// Main code
auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> int
{

    UDPConnection connection(SERVER_PORT, CLIENT_PORT);
    std::thread sendThread([&]() {
        while (true) {
            std::array<char, 255> buffer;
            // packageToSendBuffer(outPack, buffer.data());

            [[maybe_unused]] int n = connection.writeDatagram(buffer);

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    sendThread.detach(); // Detach the thread to run independently
    vek::Package pack {};

    std::thread listenerThread([&]() {
        std::array<char, 255> buffer;
        while (true) {
            int n = connection.readDatagram(buffer);
            for (int i = 0; i < n; i++) {
                // std::cout << buffer[i] << std::endl;
                if (vek::parseChar((unsigned char)buffer[i], &pack) > 0) {
                    std::cout << "\nparsed" << std::endl;
                    std::cout << (int)pack.magic << std::endl;
                    std::cout << (int)pack.messageId << std::endl;
                    std::cout << (int)pack.seq << std::endl;
                    std::cout << (int)pack.size << std::endl;

                    if (pack.messageId == vek::GPS_MESSAGE_ID) {
                        vek::GPSPackage decodedGPSPack;
                        vek::decodeGPSPackage(pack, decodedGPSPack);
                        std::cout << decodedGPSPack.timestamp << std::endl;
                        std::cout << decodedGPSPack.latitude << std::endl;
                        std::cout << decodedGPSPack.longitude << std::endl;
                        std::cout << decodedGPSPack.altitude << std::endl;
                        std::cout << decodedGPSPack.speed << std::endl;
                        std::cout << decodedGPSPack.heading << std::endl;
                    } else {
                        std::cout << "Message is something else" << std::endl;
                    }

                    break;
                }
            }
            // if (n > 0) {
            //     uint64_t value = 0;
            //     value = vek::readFromBuffer<uint8_t>((uint8_t*)buffer.data(), 1);
            //     std::cout << "Received message: " << value << std::endl;
            // }

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