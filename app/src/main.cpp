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
    Logger::debug("<beginning of application>");

    Gui::initialize();
    Config::initialize();
}

void finalize() noexcept
{
    Config::save();
    Gui::finalize();

    SDL_Quit();

    Logger::debug("<end of application>");
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
            running = processForCurrentState();
        }
        catch (std::exception& error)
        {
#ifdef _DEBUG
            LOGD << error.what();
#endif
            setAppError(StringUtil::format("General error: %s", error.what()));
        }

        // check if state changes in the next loop
        if (getNextState() == State::None)
        {
            Gui::drawGui();
            try
            {
                Gui::doReservedFuncs();
            }
            catch (ContinuableException& ce)
            {
                Logger::debug(ce.what());
                setAppError(ce.getErrorMessage().c_str());
                setNextState(ce.getNextState());
            }
            catch (std::exception& error)
            {
                UncontinuableException uce(error.what(), ERROR_WHEN_RESFUNC_ANY);
                Logger::error(uce);
                Gui::showMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error by unexpected cause");
                throw std::runtime_error("");
            }
            Gui::clearReservedFuncs();
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
        ImGuiProject::loop();
    }
    catch (std::runtime_error&)
    {
        ImGuiProject::finalize();
        exit(EXIT_FAILURE);
    }

    ImGuiProject::finalize();

    return 0;
}