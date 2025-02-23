#pragma once

#include "ImGuiPanel.hpp"

class MainPanelGUI : public ImGuiPanel
{
public:
    MainPanelGUI();
    ~MainPanelGUI();
    void render() override;
private:
};

