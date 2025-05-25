#include "ImGuiEngine.hpp"
#include "ImGuiPanel.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <format>

ImGuiEngine::ImGuiEngine(GLFWwindow* window)
    : _window(window)
{
}

void ImGuiEngine::addPanel(const std::string& name, ImGuiPanel* panel)
{
    if (panels.find(name) != panels.end()) {
        std::cout << "Panel with name " << name << " already exists" << std::endl;
        return;
    }
    panels[name] = panel;
}

void ImGuiEngine::setupLayout()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    static ImGuiID dockspace_id = ImGui::GetID("Dockspace");

    ImGui::DockSpaceOverViewport(dockspace_id, viewport);

    // Create dockspace layout on first run
    static auto first_time = true;
    if (first_time) {
        first_time = false;

        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        // Set the dockspace to fill the entire viewport
        ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

        // Split the dockspace into sections with better proportions
        ImGuiID dock_main_id = dockspace_id;
        ImGuiID dock_bottom_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.25f, nullptr, &dock_main_id);
        ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.58f, nullptr, &dock_main_id);
        ImGuiID dock_left_left_id = ImGui::DockBuilderSplitNode(dock_left_id, ImGuiDir_Left, 0.30f, nullptr, &dock_left_id);

        // Dock windows into the layout
        ImGui::DockBuilderDockWindow("Transmitter Test", dock_left_id);
        ImGui::DockBuilderDockWindow("Reciever Test", dock_main_id);
        ImGui::DockBuilderDockWindow("Message Info", dock_bottom_id);
        ImGui::DockBuilderDockWindow("Settings", dock_left_left_id);

        // Finalize the docking layout
        ImGui::DockBuilderFinish(dockspace_id);
    }
}

void ImGuiEngine::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    setupLayout();

    // Render all panels
    for (auto& panel : panels) {
        panel.second->render();
    }

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ImGuiEngine::init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    const char* glsl_version = "#version 460";
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

void ImGuiEngine::shutdown()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
