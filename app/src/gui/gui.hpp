﻿#pragma once
#include "state.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Gui
{

extern std::vector<std::function<void()>> reserved_funcs;

void initialize();
void finalize() noexcept;
void drawGui();
void showMessageBox(Uint32 flags, const char* title, const char* message) noexcept;
void doReservedFuncs();
void clearReservedFuncs() noexcept;

// sub modules
#ifdef _DEBUG
namespace Debug
{
void drawDebugMenuBar(const ImVec2& viewport_pos);
void drawDebugWindows(int window_w, int window_h, State current_state);
} // Debug
#endif
} // Gui
} // ImGuiApp
