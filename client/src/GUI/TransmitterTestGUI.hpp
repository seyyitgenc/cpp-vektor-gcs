#pragma once

#include "ImGuiPanel.hpp"

class TransmitterTestGUI : public ImGuiPanel
{
public:
    TransmitterTestGUI();
    ~TransmitterTestGUI();
    void render() override;
private:
};

