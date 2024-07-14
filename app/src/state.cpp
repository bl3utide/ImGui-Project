#include "common.hpp"
#include "state.hpp"
#include "config/config.hpp"
#ifdef _DEBUG
#include "logger.hpp"
#endif

// TODO change app namespace
namespace ImGuiProject
{

// public
#ifdef _DEBUG
const char* STATE_STR[static_cast<int>(State::_COUNT_)] =
{
    "InitInternalData",
    "ApplyConfig",
    "Idle",
    "PrepareToExit",
    "None"
};
#endif

// private
State state_ = State::InitInternalData;
State next_state_ = State::None;    // the next state that change in the next loop

bool processForCurrentState()
{
    switch (state_)
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
        return false;
        break;
    default:
        break;
    }

    return true;
}

State getState() noexcept
{
    return state_;
}

State getNextState() noexcept
{
    return next_state_;
}

void setNextState(State target_state, const bool force_mod) noexcept
{
    if (target_state == State::None)
        return;

    if (next_state_ == State::None || force_mod)
    {
        next_state_ = target_state;
#ifdef _DEBUG
        LDEBUG << "setNextState: [" << static_cast<int>(next_state_) << "]"
            << STATE_STR[static_cast<int>(next_state_)]
            << " (current: " << STATE_STR[static_cast<int>(state_)] << ")";
#endif
    }
    else
    {
#ifdef _DEBUG
        LDEBUG << "*** called multiple times in one loop ***";
        LDEBUG << " -> current_state: " << STATE_STR[static_cast<int>(state_)];
        LDEBUG << " -> next_state:    " << STATE_STR[static_cast<int>(next_state_)];
        LDEBUG << " -> arg:           " << STATE_STR[static_cast<int>(target_state)];
#endif
    }
}

void transitionState() noexcept
{
    state_ = next_state_;
    next_state_ = State::None;
#ifdef _DEBUG
    LDEBUG << "State changed to [" << static_cast<int>(state_) << "]"
        << STATE_STR[static_cast<int>(state_)];
#endif
}

} // ImGuiProject
