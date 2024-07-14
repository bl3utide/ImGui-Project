/*
    ImGui Project
    0.3.0
*/
/*
    (Project Name)
    Copyright (C) 20xx bl3utide <bl3utide@gmail.com>
    1.0.0
*/
#include "common.hpp"
#include "error.hpp"
#include "state.hpp"
#include "config/config.hpp"
#include "gui/gui.hpp"
#include "logger.hpp"

// TODO change app namespace
namespace ImGuiProject
{

void initialize()
{
    Logger::initialize();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        throw std::runtime_error("SDL_Init error");
    }

    Gui::initialize();
    Config::initialize();
}

void finalize() noexcept
{
    Config::save();
    Gui::finalize();

    SDL_Quit();
}

void loop()
{
    SDL_Event event;
    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                setNextState(State::PrepareToExit);
        }

        try
        {
            switch (getState())
            {
                case State::InitInternalData:
                    setNextState(State::ApplyConfig);
                    break;
                case State::ApplyConfig:
                    Config::load();
                    // TODO apply config data to all corresponding modules
                    setNextState(State::Idle);
                    break;
                case State::Idle:
                    break;
                case State::PrepareToExit:
                    // TODO update config data from all corresponding modules
                    running = false;
                    break;
                default:
                    break;
            }
        }
        catch (std::exception& error)
        {
#ifdef _DEBUG
            LOGD << error.what();
#endif
            setAppError(StringUtil::format("General error: %s", error.what()));
        }

        if (getNextState() == State::None)
        {
            try
            {
                Gui::drawGui();
            }
            catch (std::exception& error)
            {
#ifdef _DEBUG
                LOGD << error.what();
#endif
                setAppError(StringUtil::format("Gui error: %s", error.what()));
            }
        }
        else
        {
            transitionState();
        }

        SDL_Delay(5);
    }
}

} // ImGuiApp

int main(int, char**)
{
    try
    {
        ImGuiProject::initialize();
    }
    catch (std::exception& e)
    {
#ifdef _DEBUG
        LOGD << e.what();
#endif
        LERROR << e.what();
        ImGuiProject::Gui::showMessageBox(SDL_MESSAGEBOX_ERROR, "Error", e.what());
        ImGuiProject::finalize();
        exit(EXIT_FAILURE);
    }

    ImGuiProject::loop();
    ImGuiProject::finalize();

#ifdef _DEBUG
    LOGD << "<end of application>";
#endif
    return 0;
}