#pragma once

#include <iostream>
#include <unordered_map>

class ImGuiPanel;
class GLFWwindow;


class ImGuiEngine
{
public:
    ImGuiEngine(GLFWwindow* window);
    ~ImGuiEngine();
    void addPanel(const std::string& name, ImGuiPanel *panel);
    void render();
    bool init();
    void shutdown();

private:

    std::unordered_map<std::string, ImGuiPanel*> panels;
    GLFWwindow* _window;
};
