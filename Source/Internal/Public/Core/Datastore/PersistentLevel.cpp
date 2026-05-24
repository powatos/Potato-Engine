/** @file PersistentLevel.cpp */

#include "Util/Vector2.hpp"
#include "Archivable.hpp"
#include "Game/Control/GameInstance.hpp"
#include "Debug/Debug.hpp"
#include "Game/World.hpp"

#include "fmt/core.h"
#include "nlohmann/json.hpp"
#include "PersistentLevel.hpp"

using json = nlohmann::json;

static json safeGetJson(const std::filesystem::path& path);
static std::filesystem::path getDataDir();

PersistentLevel::PersistentLevel(const std::string& saveFileName) {
    
    std::filesystem::path saveDir = getDataDir() / "Saves";
    std::filesystem::create_directories(saveDir);

    saveFileAbsPath = saveDir / saveFileName;

}   

bool PersistentLevel::LoadStaticActors() {
    json Save = safeGetJson(saveFileAbsPath);
    json StaticActors = Save["StaticActors"];

    bool allSuccessful = true;

    World* world = GameInstance::get()->GetWorld();
    __ArchiveType& Archive = __Archive::_GetArchive();

    LOG_DEFAULT(LogType::INFO, "Loading static actors from persistent level");

    for (const auto& [ClassID, posList] : StaticActors.items()) {
        
        auto it = Archive.find(ClassID);
        // if ClassID not found in archive, continue to skip
        if (it == Archive.end()) {
            LOG_DEFAULT(LogType::WARNING, "Unkown ClassID in factory: {} - skipped loading", ClassID);
            continue;
        }

        auto constructor = it->second;
        // if constsructor not found, continue to skip
        if (constructor == nullptr) {
            LOG_DEFAULT(LogType::WARNING, "Bad function reference in archive for class: {} - skipped loading", ClassID);
            continue;
        }
        
        LOG_DEFAULT(LogType::INFO, "Loading static actors of class: {}", ClassID);

        for (const auto& pos : posList) {
            
            if (!pos.is_array() || pos.size() != 2) {
                LOG_DEFAULT(LogType::WARNING, "Invalid position data for class: {} - skipped loading", ClassID);
                continue;
            } 

            Vector2 Position;

            try {

                float x = pos[0].get<float>();
                float y = pos[1].get<float>();
                Position = Vector2(x,y);
                
            } catch (const json::type_error& e) {

                LOG_DEFAULT(LogType::WARNING, "Failed to parse data for actor: {} - skipped loading", e.what());
                allSuccessful = false;

                continue;
            }
            
            Archivable* obj = constructor();

            // if returns nullptr, skip
            if (obj == nullptr) {
                LOG_DEFAULT(LogType::WARNING, "Object could not be constructor for class: {} - skipped loading", ClassID);
                allSuccessful = false;
                continue;
            }

            if (Actor* addedActor = world->AddtoPool(dynamic_cast<Actor*>(obj))) {
                addedActor->SetPosition(Position);
            } else {
                allSuccessful = false;
                LOG_DEFAULT(LogType::WARNING, "Failed to load static actor when adding to actor pool: {} - skipped loading", ClassID);
                delete obj;
            }
        }

    }


    LOG_DEFAULT(LogType::INFO, "Static actors loaded {}", allSuccessful ? "successfully" : "unsuccessfully");
    return allSuccessful;
}

#pragma region Data getters and writers

int PersistentLevel::GetIntData( std::string key ) const {
    json Save = safeGetJson(saveFileAbsPath);

    return Save["Data"][key].get<int>();
}
float PersistentLevel::GetFloatData( std::string key ) const {
    json Save = safeGetJson(saveFileAbsPath);

    return Save["Data"][key].get<float>();
}
std::string PersistentLevel::GetStringData( std::string key ) const {
    json Save = safeGetJson(saveFileAbsPath);

    return Save["Data"][key].get<std::string>();
}
Vector2 PersistentLevel::GetVector2Data( std::string key ) const {
    json Save = safeGetJson(saveFileAbsPath);

    json vecJson = Save["Data"][key];
    return Vector2(vecJson[0].get<float>(), vecJson[1].get<float>());
}

void PersistentLevel::WriteIntData( std::string key, int value ) {
    json Save = safeGetJson(saveFileAbsPath);

    Save["Data"][key] = value;
}
void PersistentLevel::WriteFloatData( std::string key, float value ) {
    json Save = safeGetJson(saveFileAbsPath);

    Save["Data"][key] = value;
}
void PersistentLevel::WriteStringData( std::string key, std::string value ) {
    json Save = safeGetJson(saveFileAbsPath);

    Save["Data"][key] = value;
}
void PersistentLevel::WriteVector2Data( std::string key, const Vector2& value ) {
    json Save = safeGetJson(saveFileAbsPath);

    Save["Data"][key] = { value.x, value.y };
}

#pragma endregion

static json safeGetJson(const std::filesystem::path& path) {
    json parsed;

    if (!std::filesystem::exists(path)) {
        LOG_DEFAULT(LogType::ERROR, "Save file not found at {}", path.c_str());
        return parsed;
    }

    std::ifstream file(path);

    if (!file.is_open()) {
        LOG_DEFAULT(LogType::ERROR, "Could not open save file at {}", path.c_str());
        return parsed;
    }

    try {
        parsed = json::parse(file);
    } catch (const json::parse_error& e) {
        LOG_DEFAULT(LogType::ERROR, "Failed to parse save file at {}: {}", path.c_str(), e.what());   
    }

    return parsed;

}

static std::filesystem::path getDataDir() {
    static std::filesystem::path dataDir;

#if defined(_WIN32)
    // windows: C:\Users\{User}\AppData\Roaming\PotatoEngine\Data
    const char* appData = std::getenv("APPDATA");
    if (appData) {
        saveDir = std::filesystem::path(appData) / "PotatoEngine" / "Data";
    } else {
        LOG_DEFAULT(LogType::ERROR, "APPDATA environment variable not found while parsing data");
    }
#elif defined(__APPLE__)
    // macOS: /Users/{User}/Library/Application Support/PotatoEngine/Data
    const char* home = std::getenv("HOME");
    if (home) {
        dataDir = std::filesystem::path(home) / "Library" / "Application Support" / "PotatoEngine" / "Data";
    } else {    
        LOG_DEFAULT(LogType::ERROR, "HOME environment variable not found while parsing data");
    }
#elif defined(__linux__)
    // linux: /home/{User}/.local/share/PotatoEngine/Data
    const char* xdgData = std::getenv("XDG_DATA_HOME");
    if (xdgData) {
        dataDir = std::filesystem::path(xdgData) / "PotatoEngine" / "Data";
    } else {
        const char* home = std::getenv("HOME");
        if (home) {
            dataDir = std::filesystem::path(home) / ".local" / "share" / "PotatoEngine" / "Data";
        } else {
            LOG_DEFAULT(LogType::ERROR, "HOME environment variable not found while parsing data");
        }
    }
#endif
    
    std::filesystem::create_directories(dataDir);
    return dataDir;
}





