﻿#pragma once
#include "config/cv.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Config
{
namespace Writer
{

void cvToIni(const Cv& cv, mINI::INIStructure& is) noexcept;

} // Writer
} // Config
} // ImGuiProject
