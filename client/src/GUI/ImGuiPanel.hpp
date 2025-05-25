#pragma once

#include <string>

class ImGuiPanel
{
public:
    ImGuiPanel(const std::string& name);
    ~ImGuiPanel();

    virtual void render() = 0;
private:

    std::string _name;
};

