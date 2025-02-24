#pragma once

#include "ImGuiPanel.hpp"

class SettingsGUI : public ImGuiPanel
{
public:
    SettingsGUI();
    ~SettingsGUI();
    void render() override;
    
private:
};