/** @file Debug.hpp */
#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "fmt/core.h"

class Logger;
enum class LogType;

/**
 * @brief Default log object
 * @details This is a Logger object reference. Use as function call: `LOG_DEFAULT(...)`
 * @see Logger::operator()
 */
extern Logger LOG_DEFAULT;

#define logtypes \
    X(INFO) \
    X(WARNING) \
    X(ERROR) \
    X(VITAL) \
    X(DEBUG)

#define X(name) name,
enum class LogType { logtypes };
#undef X

struct LogEntry
{
    std::string timestamp;
    std::string message;
    LogType type;
};

/**
 * @brief Logging functionality
 * @details Use engine externed Logger objects for logging \n To create a custom logger, see Debug
 */
class Logger
{
public:
    Logger();

    /**
     * @brief Logs message to log file with given type
     * * @tparam Args arguments for formatting
     * @param type type of log message
     * @param message message to log
     */
    template <typename... Args>
    bool operator ()(LogType type, std::string_view message, Args&&... args) {
        const std::string timestamp = getTimestampUTC(); // minimize latency
        const std::string formatted = fmt::format(message, std::forward<Args>(args)...);

        pushLog( LogEntry{
            std::move(timestamp),
            std::move(formatted),
            type
        } );

        return true;
    }

    inline static const std::unordered_map<LogType, std::string> LogColorMap = {
        {LogType::INFO, "\x1b[0;37m"},
        {LogType::WARNING, "\x1b[0;33m"},
        {LogType::ERROR, "\x1b[0;31m"},
        {LogType::VITAL, "\x1b[1;35m"},
        {LogType::DEBUG, "\x1b[0;34m"}
    };

    #define X(name) { LogType::name, std::string(#name) },
    inline static const std::unordered_map<LogType, std::string> LogNameMap = {
        logtypes
    };
    #undef X

    void init(const char* path);
    ~Logger();

private:
    const std::string getTimestampUTC() const;

    void pushLog(LogEntry entry);
    void processLogs();

    struct LogAsyncImpl;
    std::unique_ptr<LogAsyncImpl> i_LogAsyncImpl;
};

/**
 * @brief Contains global debug functionality
 * @details Ensure all Logger objects are initialized under the @ref BindDebugLogs() "binding".
 * 
 * To use a custom logger:
 * - extern logger: `extern Logger {logger}`
 * - add to @ref Debug::BindDebugLogs "bindings"
 * - instantiate at the top of source file: `Logger {logger}`
 */
namespace DebugLogs
{
    // construct global Logger objects, bind to log files
    /**
     * @brief Constructs global logger objects, bind to log files
     * @details This method is called internally, but it must be updated with custom logger objects
     * to operate properly
     * @warning Ensure `LOG_DEFAULT.init(...)` is called with a valid log file path
     */
    inline void BindDebugLogs() {
        LOG_DEFAULT.init("logs/debug.log");
    }
}

