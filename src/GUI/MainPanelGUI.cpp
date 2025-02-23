#include "MainPanelGUI.hpp"

#include <imgui.h>

MainPanelGUI::MainPanelGUI() : ImGuiPanel("Main Panel") {}

MainPanelGUI::~MainPanelGUI()
{
}

void MainPanelGUI::render() {
    ImGui::Begin("Main Panel");
    ImGui::Text("Hello, world!");
    ImGui::End();
}
