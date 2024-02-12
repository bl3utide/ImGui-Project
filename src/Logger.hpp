#pragma once
#ifdef _DEBUG

#include "StringUtil.hpp"

// TODO change app namespace
namespace ImGuiApp
{
namespace Logger
{

class Log
{
public:
    int log_id;
    std::string timestamp;
    std::string category;
    std::string function;
    std::string line;
    std::string text;

    Log() : log_id(0), timestamp(""), category(""), function(""), line(""), text("")
    {}

    Log(const std::string& message)
    {
        std::regex re("^(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3}) (\\S+) \\[([^@]+)@(\\d+)\\] (.+)$");
        std::smatch m;
        if (std::regex_search(message, m, re))
        {
            log_id = _next_log_id;
            ++_next_log_id;

            timestamp = m[1];
            category = m[2];
            function = m[3];
            line = m[4];
            text = m[5];
        }
    }

private:
    static int _next_log_id;
};

extern std::list<Log> logs;
extern const size_t MAX_DISPLAY_LOGS;
/* TODO 上のバージョンがうまくいったら、下のバージョンは消す
extern std::list<plog::util::nstring> debug_log;
extern const size_t MAX_DEBUG_LOG_SIZE;
*/

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
        std::string str = Formatter::format(record);
        AppLogger::Log log = AppLogger::Log(str);
        AppLogger::logs.push_front(log);
        if (AppLogger::logs.size() > AppLogger::MAX_DISPLAY_LOGS)
            AppLogger::logs.resize(AppLogger::MAX_DISPLAY_LOGS);
        /* 上のバージョンがうまくいったら、下のバージョンは消す
        AppLogger::debug_log.push_front(str);
        if (AppLogger::debug_log.size() > AppLogger::MAX_DEBUG_LOG_SIZE)
            AppLogger::debug_log.resize(AppLogger::MAX_DEBUG_LOG_SIZE);
            */
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

        util::nostringstream ss;
        ss << t.tm_year + 1900 << "-"
            << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mon + 1 << PLOG_NSTR("-")
            << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mday << PLOG_NSTR(" ");
        ss << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_hour << PLOG_NSTR(":")
            << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_min << PLOG_NSTR(":")
            << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_sec << PLOG_NSTR(".")
            << std::setfill(PLOG_NSTR('0')) << std::setw(3) << record.getTime().millitm << PLOG_NSTR(" ");
        ss << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << severityToString(record.getSeverity()) << PLOG_NSTR(" ");
        ss << PLOG_NSTR("[") << record.getFunc() << PLOG_NSTR("@") << record.getLine() << PLOG_NSTR("] ");
        ss << record.getMessage() << PLOG_NSTR("\n");

        return ss.str();
    }
};

} // plog
#endif