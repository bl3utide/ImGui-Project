#pragma once

#include "state.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Gui
{

void initialize(const std::string& title, const std::string& version, const std::string& copyright);
void finalize() noexcept;
void drawGui();

// sub modules
#ifdef _DEBUG
namespace Debug
{
void drawDebugMenuBar(const ImVec2 viewport_pos);
void drawDebugWindows(const int window_w, const int window_h, const State current_state);
} // Debug
#endif
} // Gui
} // ImGuiApp
