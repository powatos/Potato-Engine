#pragma once

#include <fstream>
#include <unordered_map>

class Logger;
enum class LogType;

/**
 * @brief Default log object
 * @details This is a Logger object reference. Use as function call: `LOG_DEFAULT(...)`
 * To use a custom logger:
 * - extern logger: `extern Logger {logger}`
 * - add to @ref Debug::BindDebugLogs "bindings"
 * - instantiate at the top of source file: `Logger {logger}`
 * @see Logger::operator()
 */
extern Logger LOG_DEFAULT;

/**
 * @brief Logging functionality
 * @details Use engine externed Logger objects for logging
 */
class Logger
{
    const char* LogFilePath;

    std::ofstream LogFile;

public:

    // returns true if successful
    bool operator () (LogType type, const std::string& message);

    void init(const char* path);
    ~Logger();
};

#define logtypes \
    X(INFO) \
    X(WARNING) \
    X(ERROR) \
    X(VITAL) \
    X(DEBUG)

#define X(name) name,
enum class LogType { logtypes };
#undef X

/**
 * @brief Contains global debug functionality
 * @details Ensure all Logger objects are initialized under the @ref BindDebugLogs() "binding".
 */
namespace Debug
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

