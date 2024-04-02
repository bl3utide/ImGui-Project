#pragma once

// TODO change app namespace
namespace ImGuiProject
{
namespace Config
{

enum class Section : int
{
    // TODO add ini sections
    // ex)
    NewSection,
    _COUNT_,
};

enum class Key : int
{
    // TODO add ini keys
    // ex)
    // [NewSection]
    NewKey1,
    NewKey2,
    NewKey3,

    _COUNT_,
};

extern const char* SECTION_NAMES[static_cast<int>(Section::_COUNT_)];
extern const char* KEY_NAMES[static_cast<int>(Key::_COUNT_)];

} // Config
} // ImGuiProject
