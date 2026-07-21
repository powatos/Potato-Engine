/** @file DataManager.cpp */

#include "Debug/Log.hpp"

#include "DataManager.hpp"

path DataManager::GetDataDir() {
    
    path dataDir = std::filesystem::current_path() / "Data";

    if (!std::filesystem::exists(dataDir)) {
        std::filesystem::create_directories(dataDir);
    }

    return dataDir;
}

path DataManager::GetSaveDir() {
    path saveDir;

#if defined(_WIN32)
    // windows: C:\Users\{User}\AppData\Roaming\PotatoEngine\Saves
    const char* appData = std::getenv("APPDATA");
    if (appData) {
        saveDir = path(appData) / "PotatoEngine" / "Saves";
    } else {
        LOG_DEFAULT(LogType::ERROR, "APPDATA environment variable not found while parsing saves");
    }
#elif defined(__APPLE__)
    // macOS: /Users/{User}/Library/Application Support/PotatoEngine/Saves
    const char* home = std::getenv("HOME");
    if (home) {
        saveDir = path(home) / "Library" / "Application Support" / "PotatoEngine" / "Saves";
    } else {    
        LOG_DEFAULT(LogType::ERROR, "HOME environment variable not found while parsing saves");
    }
#elif defined(__linux__)
    // linux: /home/{User}/.local/share/PotatoEngine/Saves
    const char* xdgData = std::getenv("XDG_DATA_HOME");
    if (xdgData) {
        saveDir = path(xdgData) / "PotatoEngine" / "Saves";
    } else {
        const char* home = std::getenv("HOME");
        if (home) {
            saveDir = path(home) / ".local" / "share" / "PotatoEngine" / "Saves";
        } else {
            LOG_DEFAULT(LogType::ERROR, "HOME environment variable not found while parsing saves");
        }
    }
#endif
    
    if (!saveDir.empty()) {
        std::filesystem::create_directories(saveDir);
    }
    return saveDir;
}
