﻿#pragma once

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
    _COUNT_,
};

#ifdef _DEBUG
enum class FontDebug : int
{
    Text = static_cast<int>(Font::_COUNT_),
    ProcHead,
    ProcHex,
    _COUNT_,
};
#endif

void addAllFonts();
#ifdef _DEBUG
void addAllFontsDebug();
#endif

} // Gui
} // ImGuiProject
