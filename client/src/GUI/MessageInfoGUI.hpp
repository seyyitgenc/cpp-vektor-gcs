#pragma once

#include "ImGuiPanel.hpp"

class MessageInfoGUI : public ImGuiPanel {
public:
    MessageInfoGUI();
    ~MessageInfoGUI() = default;
    MessageInfoGUI(const MessageInfoGUI&) = default;
    MessageInfoGUI(MessageInfoGUI&&) = default;

    void render() override;

private:
};
