#pragma once
#ifdef _DEBUG

// TODO change app namespace
namespace ImGuiApp
{
namespace Logger
{

extern std::list<plog::util::nstring> debug_log;
extern const size_t MAX_DEBUG_LOG_SIZE;

} // Logger
} // ImGuiApp

namespace plog
{

template<class Formatter>
class DebugLogAppender : public IAppender
{
public:
    virtual void write(const Record& record)
    {
        namespace AppLogger = ImGuiApp::Logger;
        plog::util::nstring str = Formatter::format(record);
        AppLogger::debug_log.push_front(str);
        if (AppLogger::debug_log.size() > AppLogger::MAX_DEBUG_LOG_SIZE)
            AppLogger::debug_log.resize(AppLogger::MAX_DEBUG_LOG_SIZE);
    }
};

class LogFormatter
{
public:
    static util::nstring header()
    {
        return util::nstring();
    }

    static util::nstring format(const Record& record)
    {
        tm t;
        util::localtime_s(&t, &record.getTime().time);

        util::nstringstream ss;
        ss << t.tm_year + 1900 << "-"
            << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mon + 1 << PLOG_NSTR("-")
            << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mday << PLOG_NSTR(" ");
        ss << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_hour << PLOG_NSTR(":")
            << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_min << PLOG_NSTR(":")
            << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_sec << PLOG_NSTR(".")
            << std::setfill(PLOG_NSTR('0')) << std::setw(3) << record.getTime().millitm << PLOG_NSTR(" ");
        ss << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << severityToString(record.getSeverity()) << PLOG_NSTR(" ");
        ss << PLOG_NSTR("[") << record.getFunc() << PLOG_NSTR("] ");
        ss << record.getMessage() << PLOG_NSTR("\n");

        return ss.str();
    }
};

} // plog
#endif