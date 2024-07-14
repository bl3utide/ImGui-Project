#pragma once

#include <stdexcept>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <regex>

#include <SDL.h>
#include <SDL_opengl.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl2.h>

#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Appenders/IAppender.h>

#include <mini/ini.h>

#include "util/gui_util.hpp"
#include "util/string_util.hpp"

namespace ImGuiProject
{
#define DEF_APP_NAME        "ImGuiProject"      // TODO fix app name
#define DEF_APP_VERSION     "1.0"
#define DEF_APP_DEV_BY      "bl3utide"
#define DEF_APP_DEV_YR      2024                // TODO fix dev year
#define DEF_APP_TITLE       "ImGui Project"     // TODO fix app title

const std::string APP_NAME = DEF_APP_NAME;
} // ImGuiProject
