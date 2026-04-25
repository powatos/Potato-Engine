
#include <chrono>
#include <iomanip>

#include "fmt/chrono.h"
#include "Debug.h"

Logger LOG_DEFAULT;

static const std::unordered_map<LogType, std::string> LogColorMap = {
        {LogType::INFO, "\e[1;37m"},
        {LogType::WARNING, "\e[0;33m"},
        {LogType::ERROR, "\e[1;31m"},
        {LogType::VITAL, "\e[1;4;35m"}
};

void Logger::init(const char* path){    
    LogFile.open(path, std::ios::app);
    LogFile << "\n\n\n"; // delimit on every binding
}

std::string getTimestampUTC() {
    using namespace std::chrono;

    auto now = system_clock::now();
    auto s = time_point_cast<seconds>(now);
    auto ms = duration_cast<milliseconds>( now - s ).count();

    // threadsafe (linux specific)
    std::time_t t = system_clock::to_time_t(now);
    std::tm tm{};
    gmtime_r(&t, &tm);

    std::string timestamp = fmt::format("{:%H:%M:%S}.{:03}", tm, ms);

    return timestamp;
}

bool Logger::operator () (LogType type, const std::string& message) {
    std::string timestamp = getTimestampUTC(); // minimize latency

    if (!LogFile.is_open()) { return false; }

    std::string colorMod = LogColorMap.at(type);
    
    LogFile << timestamp << " - ";
    LogFile << colorMod << message << "\e[0m" << std::endl;

    return true;
}

Logger::~Logger() {
    if (LogFile.is_open()) {
        LogFile.close();
    }
}