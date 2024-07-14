#include "common.hpp"
#include "error.hpp"
#include "main.hpp"
#include "state.hpp"
#include "config/config.hpp"
#include "gui/gui.hpp"
#include "logger.hpp"

// TODO change app namespace
namespace ImGuiProject
{

// private
const std::string APP_NAME = DEF_APP_NAME;
const std::string APP_VERSION = DEF_APP_VERSION;
const std::string APP_COPYRIGHT = StringUtil::format("Copyright (C) %d %s", DEF_APP_DEV_YR, DEF_APP_DEV_BY);
const std::string APP_TITLE = DEF_APP_TITLE;
const std::string CONFIG_FILE_NAME = StringUtil::format("%s.ini", APP_NAME.c_str());
#ifdef _DEBUG
const std::string DEBUG_FILE_NAME = StringUtil::format("%s.debug.log", APP_NAME.c_str());
#endif
const std::string ERROR_FILE_NAME = StringUtil::format("%s.error.log", APP_NAME.c_str());

void initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        throw std::runtime_error("SDL_Init error");
    }

    Gui::initialize(APP_TITLE, APP_VERSION, APP_COPYRIGHT);
    Config::initialize();
}

void finalize() noexcept
{
    Config::save(CONFIG_FILE_NAME);
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
                    Config::load(CONFIG_FILE_NAME);
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
    enum LogId
    {
        Error = 1,
    };

#ifdef _DEBUG
    static plog::DebugLogAppender<plog::DebugLogFormatter> debugLogAppender;
    plog::init<plog::DebugLogFormatter>(plog::debug, ImGuiProject::DEBUG_FILE_NAME.c_str()).addAppender(&debugLogAppender);
    LOGD << "<beginning of application>";
#endif
    plog::init<plog::ErrorLogFormatter, LogId::Error>(plog::error, ImGuiProject::ERROR_FILE_NAME.c_str());
#define LOGE LOGE_(1)
    try
    {
        ImGuiProject::initialize();
    }
    catch (std::exception& e)
    {
#ifdef _DEBUG
        LOGD << e.what();
#endif
        LOGE << e.what();
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