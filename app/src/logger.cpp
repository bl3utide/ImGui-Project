#include "common.hpp"
#include "logger.hpp"

#ifdef _DEBUG
// TODO change app namespace
namespace ImGuiProject
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