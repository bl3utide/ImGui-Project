#ifdef _DEBUG
#include "Common.hpp"
#include "Logger.hpp"

// TODO change app namespace
namespace ImGuiApp
{
namespace Logger
{

// public
std::list<plog::util::nstring> debug_log;
const size_t MAX_DEBUG_LOG_SIZE = 100;

} // Logger
} // ImGuiApp
#endif