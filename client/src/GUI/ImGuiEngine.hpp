#pragma once

#include <iostream>
#include <unordered_map>

class ImGuiPanel;
class GLFWwindow;

class ImGuiEngine {
public:
    ImGuiEngine(GLFWwindow* window);
    ImGuiEngine(const ImGuiEngine&) = default;
    ImGuiEngine(ImGuiEngine&&) = default;

    ~ImGuiEngine() = default;
    void addPanel(const std::string& name, ImGuiPanel* panel);
    void render();
    auto init() -> bool;
    void shutdown();

    void setupLayout();

private:
    std::unordered_map<std::string, ImGuiPanel*> panels;
    GLFWwindow* _window;
};
