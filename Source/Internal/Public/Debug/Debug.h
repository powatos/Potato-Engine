#pragma once

#include <fstream>
#include <unordered_map>

class Logger;
enum class LogType;
extern Logger LOG_DEFAULT;

class Logger
{
    const char* LogFilePath;

    std::ofstream LogFile;

public:

    /** @return bool : true if successful */
    bool operator () (LogType type, const std::string& message);

    void init(const char* path);
    ~Logger();
};

#define logtypes \
    X(INFO) \
    X(WARNING) \
    X(ERROR) \
    X(VITAL)

#define X(name) name,
enum class LogType { logtypes };
#undef X

namespace Debug
{
    // construct global Logger objects, bind to log files
    inline void BindDebugLogs() {
        LOG_DEFAULT.init("logs/debug.log");
    }
}

