#include "Constants.hpp"
#include "GUI/ImGuiEngine.hpp"
#include "GUI/MessageInfoGUI.hpp"
#include "GUI/RecieverTestGUI.hpp"
#include "GUI/SettingsGUI.hpp"
#include "GUI/TransmitterTestGUI.hpp"
#include "Globals.hpp"

namespace {

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

} // namespace

// Main code
auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> int
{
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
    engine.addPanel("Reciever Test", new RecieverTestGUI());
    engine.addPanel("Transmitter Test", new TransmitterTestGUI());
    engine.addPanel("Message Info", new MessageInfoGUI());
    engine.addPanel("Settings", new SettingsGUI());

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