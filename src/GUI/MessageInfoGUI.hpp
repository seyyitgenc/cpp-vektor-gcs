#pragma once

#include "ImGuiPanel.hpp"

class MessageInfoGUI : public ImGuiPanel
{
public:
    MessageInfoGUI();
    ~MessageInfoGUI();

    void render() override;
private:

};

