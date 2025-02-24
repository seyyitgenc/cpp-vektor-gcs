#include "RecieverTestGUI.hpp"

#include "ImGuiUtils.hpp"

#include <imgui.h>

RecieverTestGUI::RecieverTestGUI() : ImGuiPanel("Reciever Test") {}

RecieverTestGUI::~RecieverTestGUI()
{
}

void RecieverTestGUI::render() {
    if (ImGui::Begin("Reciever Test")) {
        ImGui::BeginGroupPanel("Reciever Test");
        ImGui::BeginTable("Reciever Test Table", 2, ImGuiTableFlags_SizingStretchProp);

        float row_height = 23.0f; // Set the desired row height

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Team ID: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Counter: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Altitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Rocket GPS Altitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Rocket Latitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Rocket Longitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Payload GPS Altitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Payload Latitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Payload Longitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Kademe GPS Altitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Kademe Latitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Kademe Longitude: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Gyroscope X: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Gyroscope Y: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Gyroscope Z: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Accelerometer X: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Accelerometer Y: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Accelerometer Z: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("Angle : ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("State: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_height);
        ImGui::TableNextColumn();
        ImGui::Text("CRC: ");
        ImGui::TableNextColumn();
        ImGui::Text("0x00");

        ImGui::EndTable();
        ImGui::EndGroupPanel();
    }
    ImGui::End();
}