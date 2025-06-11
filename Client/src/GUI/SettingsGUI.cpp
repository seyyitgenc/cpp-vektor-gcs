#include "SettingsGUI.hpp"

#include "ImGuiUtils.hpp"

#include <imgui.h>

SettingsGUI::SettingsGUI() : ImGuiPanel("Settings") {}

SettingsGUI::~SettingsGUI() {}

void SettingsGUI::render() {
    ImGui::Begin("Settings");

    auto btnSize = ImVec2(150, 75);
    ImGui::BeginGroupPanel("Reciever Settings");
        ImGui::Button("Port Settings", btnSize);
        ImGui::Button("Close Port", btnSize);
    ImGui::EndGroupPanel();
    
    ImGui::BeginGroupPanel("Transmitter Settings");
        ImGui::Button("Port Settings2", btnSize);
        ImGui::Button("Close Port2", btnSize);
        ImGui::Button("Send Data", btnSize);
    ImGui::EndGroupPanel();
    ImGui::End();
}
