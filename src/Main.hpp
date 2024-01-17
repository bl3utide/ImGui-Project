/*
    (Project Name)
    Copyright (C) 20xx bl3utide <bl3utide@gmail.com>
*/
#pragma once

#include <string>

// TODO change Solution name
// TODO change Project name
// TODO change .sln file name
// TODO change .vcxproj file name
// TODO edit .sln file
// TODO edit .vcxproj file
// TODO change .vcxproj.filters file name
// TODO change .vcxproj.user file name

// TODO change app namespace
namespace ImGuiApp
{

#define DEF_VERSION     "1.0"
#define DEF_DEV_BY      "bl3utide"
#define DEF_DEV_YR      2024                // TODO fix dev year
#define DEF_TITLE       "ImGui Project"     // TODO fix app title
#define DEF_NAME        "ImGuiProject"      // TODO fix app name

enum class State : int
{
    InitInternalData,
    Idle,
    None,
    _COUNT_
};

extern bool has_error;
extern std::string error_message;
extern bool showing_error_message;
#ifdef _DEBUG
extern const char* STATE_STR[static_cast<int>(State::_COUNT_)];
#endif

State getState();
#ifdef _DEBUG
State getNextState();
#endif
void setNextState(State state);
std::string getAppVersion();
std::string getAppCopyright();
std::string getAppTitle();
void setAppError(const std::string& message);

} // ImGuiApp
