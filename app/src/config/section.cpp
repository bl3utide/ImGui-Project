#include "common.hpp"
#include "config/section.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Config
{

const std::unordered_map<Section, const char*> SECTION_NAMES
{
    // TODO add strings of ini section names
    // ex)
    { Section::NewSection,  "new_section" },
};

const std::unordered_map<Key, const char*> KEY_NAMES
{
    // TODO add strings of ini key names
    // ex)
    // [new_section]
    { Key::NewKey1, "new_key1" },
    { Key::NewKey2, "new_key2" },
    { Key::NewKey3, "new_key3" },
};

} // Config
} // ImGuiProject
