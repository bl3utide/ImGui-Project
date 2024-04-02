#include "common.hpp"
#include "config/section.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Config
{

const char* SECTION_NAMES[static_cast<int>(Section::_COUNT_)]
{
    // TODO add strings of ini section names
    // ex)
    "new_section"
};

const char* KEY_NAMES[static_cast<int>(Key::_COUNT_)]
{
    // TODO add strings of ini key names
    // ex)
    // [new_section]
    "new_section1",
    "new_section2",
    "new_section3",
};

} // Config
} // ImGuiProject
