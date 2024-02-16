#include "Common.hpp"
#include "Main.hpp"
#include "Gui.hpp"
#include "StringUtil.hpp"
#ifdef _DEBUG
#include "Logger.hpp"
#endif

// TODO change app namespace
namespace ImGuiProject
{

// public
bool has_error = false;
std::string error_message;
bool showing_error_message = false;
#ifdef _DEBUG
const char* STATE_STR[static_cast<int>(State::_COUNT_)] =
{
    "InitInternalData",
    "Idle",
    "None"
};
#endif

// private
const char* APP_NAME = DEF_APP_NAME;
const char* APP_VERSION = DEF_APP_VERSION;
const std::string APP_COPYRIGHT = format("Copyright (C) %d %s", DEF_APP_DEV_YR, DEF_APP_DEV_BY);
const char* APP_TITLE = DEF_APP_TITLE;
State _state;
State _next_state = State::None;            // the next state that change in the next loop
#ifdef _DEBUG
const std::string DEBUG_FILE_NAME = format("%s.debug.log", APP_NAME);
#endif

void initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        throw std::runtime_error("SDL_Init error");
    }

    _state = State::InitInternalData;

    Gui::initialize(APP_TITLE);
}

void finalize()
{
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
                running = false;
        }

        try
        {
            switch (_state)
            {
                case State::InitInternalData:
                    setNextState(State::Idle);
                    break;
                case State::Idle:
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
            setAppError(format("General error: %s", error.what()));
        }

        if (_next_state == State::None)
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
                setAppError(format("Gui error: %s", error.what()));
            }
        }
        else
        {
            _state = _next_state;
            _next_state = State::None;
#ifdef _DEBUG
            LOGD << "State changed to [" << static_cast<int>(_state) << "]"
                << STATE_STR[static_cast<int>(_state)];
#endif
        }

        SDL_Delay(5);
    }
}

State getState()
{
    return _state;
}

#ifdef _DEBUG
State getNextState()
{
    return _next_state;
}
#endif

void setNextState(State state)
{
    _next_state = state;
#ifdef _DEBUG
    LOGD << "setNextState: [" << static_cast<int>(_next_state) << "]"
        << STATE_STR[static_cast<int>(_next_state)];
#endif
}

std::string getAppVersion()
{
    return APP_VERSION;
}

std::string getAppCopyright()
{
    return APP_COPYRIGHT;
}

std::string getAppTitle()
{
    return APP_TITLE;
}

void setAppError(const std::string& message)
{
    error_message = message;
    has_error = true;
}

} // ImGuiApp

int main(int, char**)
{
#ifdef _DEBUG
    static plog::DebugLogAppender<plog::LogFormatter> debugLogAppender;
    plog::init<plog::LogFormatter>(plog::debug, ImGuiProject::DEBUG_FILE_NAME.c_str()).addAppender(&debugLogAppender);
    LOGD << "<beginning of application>";
#endif
    try
    {
        ImGuiProject::initialize();
    }
    catch (std::exception& e)
    {
#ifdef _DEBUG
        LOGD << e.what();
#endif
        printf("%s", e.what());
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