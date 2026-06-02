/** @file Debug.cpp */

#include <chrono>
#include <iomanip>

#include "fmt/chrono.h"

#include "Debug.hpp"

Logger LOG_DEFAULT;

void Logger::init(const char* path){    
    LogFile.open(path, std::ios::trunc);
    LogFile.clear();
}

std::string Logger::getTimestampUTC() {
    using namespace std::chrono;

    auto now = system_clock::now();
    auto s = time_point_cast<seconds>(now);
    auto ms = duration_cast<milliseconds>( now - s ).count();

    // threadsafe (linux specific)
    std::time_t t = system_clock::to_time_t(now);
    std::tm tm{};

#if defined(_WIN32) || defined(_WIN64)
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif

    std::string timestamp = fmt::format("{:%H:%M:%S}.{:03}", tm, ms);

    return timestamp;
}

Logger::~Logger() {
    if (LogFile.is_open()) {
        LogFile.close();
    }
}