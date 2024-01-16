#pragma once

#include <SDL.h>
#include <imgui.h>
#include "Main.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Gui
{

enum class Font : int
{
    Title,
    Version,
    OptionItem,
    OptionItemBold,
    Section,
    Text,
    TextBold,
    Debug,
    DebugProcHead,
    DebugProcHex,
    _COUNT_,
};

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

void initialize(const char* app_title);
void finalize();
void drawGui();

} // Gui
} // ImGuiProject
