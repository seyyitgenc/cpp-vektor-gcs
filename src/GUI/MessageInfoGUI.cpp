#include "MessageInfoGUI.hpp"

#include <imgui.h>

MessageInfoGUI::MessageInfoGUI()
    : ImGuiPanel("Message Info")
{
}

void MessageInfoGUI::render()
{
    ImGui::Begin("Message Info");
    ImGui::Text("Recieved 1: ");
    ImGui::SameLine();
    ImGui::TextUnformatted("[FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF]");
    ImGui::Text("Recieved 2: ");
    ImGui::SameLine();
    ImGui::TextUnformatted("[FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF]");
    ImGui::Text("Send 1:     ");
    ImGui::SameLine();
    ImGui::TextUnformatted("[FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF]");
    ImGui::Text("Send 2:     ");
    ImGui::SameLine();
    ImGui::TextUnformatted("[FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF][FF]");
    ImGui::End();
}