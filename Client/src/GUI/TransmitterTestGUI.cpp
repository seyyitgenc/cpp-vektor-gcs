#include "TransmitterTestGUI.hpp"

#include "ImGuiUtils.hpp"

#include <imgui.h>

TransmitterTestGUI::TransmitterTestGUI() : ImGuiPanel("Transmitter Test") {}

TransmitterTestGUI::~TransmitterTestGUI()
{
}

void TransmitterTestGUI::render() {
    if (ImGui::Begin("Transmitter Test")) {
        ImGui::BeginGroupPanel("Transmitter Test");
        ImGui::BeginTable("Transmitter Test Table", 2, ImGuiTableFlags_SizingStretchProp);

        static char teamID[64] = "0x00";
        static char counter[64] = "0x00";
        static char altitude[64] = "0x00";
        static char rocketGPSAltitude[64] = "0x00";
        static char rocketLatitude[64] = "0x00";
        static char rocketLongitude[64] = "0x00";
        static char payloadGPSAltitude[64] = "0x00";
        static char payloadLatitude[64] = "0x00";
        static char payloadLongitude[64] = "0x00";
        static char kademeGPSAltitude[64] = "0x00";
        static char kademeLatitude[64] = "0x00";
        static char kademeLongitude[64] = "0x00";
        static char gyroscopeX[64] = "0x00";
        static char gyroscopeY[64] = "0x00";
        static char gyroscopeZ[64] = "0x00";
        static char accelerometerX[64] = "0x00";
        static char accelerometerY[64] = "0x00";
        static char accelerometerZ[64] = "0x00";
        static char angle[64] = "0x00";
        static char state[64] = "0x00";
        static char crc[64] = "0x00";

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Team ID: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##teamID", teamID, IM_ARRAYSIZE(teamID));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Counter: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##counter", counter, IM_ARRAYSIZE(counter));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Altitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##altitude", altitude, IM_ARRAYSIZE(altitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Rocket GPS Altitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##rocketGPSAltitude", rocketGPSAltitude, IM_ARRAYSIZE(rocketGPSAltitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Rocket Latitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##rocketLatitude", rocketLatitude, IM_ARRAYSIZE(rocketLatitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Rocket Longitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##rocketLongitude", rocketLongitude, IM_ARRAYSIZE(rocketLongitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Payload GPS Altitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##payloadGPSAltitude", payloadGPSAltitude, IM_ARRAYSIZE(payloadGPSAltitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Payload Latitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##payloadLatitude", payloadLatitude, IM_ARRAYSIZE(payloadLatitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Payload Longitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##payloadLongitude", payloadLongitude, IM_ARRAYSIZE(payloadLongitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Kademe GPS Altitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##kademeGPSAltitude", kademeGPSAltitude, IM_ARRAYSIZE(kademeGPSAltitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Kademe Latitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##kademeLatitude", kademeLatitude, IM_ARRAYSIZE(kademeLatitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Kademe Longitude: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##kademeLongitude", kademeLongitude, IM_ARRAYSIZE(kademeLongitude));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Gyroscope X: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##gyroscopeX", gyroscopeX, IM_ARRAYSIZE(gyroscopeX));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Gyroscope Y: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##gyroscopeY", gyroscopeY, IM_ARRAYSIZE(gyroscopeY));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Gyroscope Z: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##gyroscopeZ", gyroscopeZ, IM_ARRAYSIZE(gyroscopeZ));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Accelerometer X: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##accelerometerX", accelerometerX, IM_ARRAYSIZE(accelerometerX));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Accelerometer Y: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##accelerometerY", accelerometerY, IM_ARRAYSIZE(accelerometerY));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Accelerometer Z: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##accelerometerZ", accelerometerZ, IM_ARRAYSIZE(accelerometerZ));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Angle : ");
        ImGui::TableNextColumn();
        ImGui::InputText("##angle", angle, IM_ARRAYSIZE(angle));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("State: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##state", state, IM_ARRAYSIZE(state));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("CRC: ");
        ImGui::TableNextColumn();
        ImGui::InputText("##crc", crc, IM_ARRAYSIZE(crc));

        ImGui::EndTable();
        ImGui::EndGroupPanel();
    }
    ImGui::End();
}