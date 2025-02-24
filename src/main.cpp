#include <GLFW/glfw3.h>

#include "Globals.hpp"
#include "GUI/ImGuiEngine.hpp"
#include "GUI/RecieverTestGUI.hpp"
#include "GUI/TransmitterTestGUI.hpp"
#include "GUI/SettingsGUI.hpp"
#include "GUI/MessageInfoGUI.hpp"

// static void glfw_error_callback(int error, const char* description)
// {
//     fprintf(stderr, "GLFW Error %d: %s\n", error, description);
// }

// Main code
int main(int, char**)
{
    // glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    gWindow = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (gWindow == nullptr)
        return false;

    glfwMakeContextCurrent(gWindow);
    glfwSwapInterval(1); // Enable vsync

    ImGuiEngine engine(gWindow);
    engine.init();
    engine.addPanel("Reciever Test", new RecieverTestGUI());
    engine.addPanel("Transmitter Test", new TransmitterTestGUI());
    engine.addPanel("Message Info", new MessageInfoGUI());
    engine.addPanel("Settings", new SettingsGUI());
    while (!glfwWindowShouldClose(gWindow))
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(gWindow, GLFW_ICONIFIED) != 0)
        {
            continue;
        }
        engine.render();
        glfwSwapBuffers(gWindow);
    }
    engine.shutdown();
    
    return 0;
}