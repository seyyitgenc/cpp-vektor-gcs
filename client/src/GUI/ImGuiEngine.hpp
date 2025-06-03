#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

class ImGuiPanel;
class GLFWwindow;

class ImGuiEngine {
public:
    ImGuiEngine(GLFWwindow* window);
    ImGuiEngine(const ImGuiEngine&) = default;
    ImGuiEngine(ImGuiEngine&&) = default;

    ~ImGuiEngine() = default;
    void addPanel(const std::string& name, std::unique_ptr<ImGuiPanel> panel);
    void render();
    auto init() -> bool;
    void shutdown();

    void setupLayout();

private:
    std::unordered_map<std::string, std::unique_ptr<ImGuiPanel>> panels;
    GLFWwindow* _window;
};
