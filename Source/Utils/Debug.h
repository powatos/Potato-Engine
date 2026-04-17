
#include <fstream>

class Logger;
extern Logger LOG_DEFAULT;


enum class LogType
{
    INFO, // white
    WARNING, // yellow
    ERROR,  // red
    VITAL   // magenta
};

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

namespace Debug
{
    // construct global Logger objects, bind to log files
    inline void BindDebugLogs() {
        LOG_DEFAULT.init("logs/debug.log");
    }
}