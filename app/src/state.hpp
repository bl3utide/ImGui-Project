#pragma once

// TODO change app namespace
namespace ImGuiProject
{

enum class State : int
{
    InitInternalData,
    ApplyConfig,
    Idle,
    PrepareToExit,
    None,
    _COUNT_
};

#ifdef _DEBUG
extern const std::unordered_map<State, const char*> STATE_STR;
#endif

bool processForCurrentState();
State getState() noexcept;
State getNextState() noexcept;
void setNextState(State state, const bool force_mod = false) noexcept;
void transitionState() noexcept;

} // ImGuiProject
