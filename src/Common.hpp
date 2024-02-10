#pragma once

#include <stdexcept>
#include <list>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_opengl.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl2.h>

#ifdef _DEBUG
#include <plog/Log.h>
#include <plog/Appenders/IAppender.h>
#endif
