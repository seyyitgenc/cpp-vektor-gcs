#include <GLFW/glfw3.h>

#include "Globals.hpp"
#include "GUI/ImGuiEngine.hpp"
#include "GUI/MainPanelGUI.hpp"

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
    engine.addPanel("test2", new MainPanelGUI());
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
    engine.render();
    engine.shutdown();
    
        // // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        // {
        //     static float f = 0.0f;
        //     static int counter = 0;

        //     ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        //     ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        //     ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //     ImGui::Checkbox("Another Window", &show_another_window);

        //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //     ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        //     if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //         counter++;
        //     ImGui::SameLine();
        //     ImGui::Text("counter = %d", counter);

        //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        //     ImGui::End();
        // }

        // // 3. Show another simple window.
        // if (show_another_window)
        // {
        //     ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        //     ImGui::Text("Hello from another window!");
        //     if (ImGui::Button("Close Me"))
        //         show_another_window = false;
        //     ImGui::End();
        // }

        // // Rendering
        // ImGui::Render();
        // int display_w, display_h;
        // glfwGetFramebufferSize(window, &display_w, &display_h);
        // glViewport(0, 0, display_w, display_h);
        // glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        // glClear(GL_COLOR_BUFFER_BIT);
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // }

    return 0;
}