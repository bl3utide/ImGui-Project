#ifdef _DEBUG
#include "Common.hpp"
#include "Logger.hpp"

// TODO change app namespace
namespace ImGuiApp
{
namespace Logger
{

// public
std::list<Log> logs;
const size_t MAX_DISPLAY_LOGS = 100;

// private
int Log::_next_log_id = 0;

} // Logger
} // ImGuiApp
#endif