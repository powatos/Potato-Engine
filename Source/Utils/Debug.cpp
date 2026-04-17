
#include <chrono>
#include <iomanip>
#include "Debug.h"

Logger LOG_DEFAULT;

void Logger::init(const char* path){    
    LogFile.open(path, std::ios::app);
    LogFile << "\n\n\n"; // delimit on every binding
}

bool Logger::operator () (LogType type, const std::string& message) {
    if (!LogFile.is_open()) { return false; }

    std::string colorMod;

    switch (type) {
        case LogType::INFO:
            colorMod = "\e[1;37m"; // white
            break;
        case LogType::WARNING:
            colorMod = "\e[0;33m"; // yellow
            break;
        case LogType::ERROR:
            colorMod = "\e[1;31m"; // red
            break;
        case LogType::VITAL:
            colorMod = "\e[1;4;35m"; // magenta
            break;
        default:
            colorMod = "";
    }
    
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    LogFile << std::put_time(std::localtime(&now), "%H:%M:%S");
    LogFile << " - " << colorMod << message << "\e[0m" << std::endl;

    return true;
}

Logger::~Logger() {
    if (LogFile.is_open()) {
        LogFile.close();
    }
}