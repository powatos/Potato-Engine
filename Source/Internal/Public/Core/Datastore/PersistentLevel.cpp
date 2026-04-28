
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
static Archivable* instantiateFromArchive(const std::string& ClassID);

PersistentLevel::PersistentLevel(const std::string& saveFileName) {
    
    saveFileAbsPath = std::filesystem::current_path() / "Saves" / saveFileName; 

}

bool PersistentLevel::LoadStaticActors() {
    json Save = safeGetJson(saveFileAbsPath);
    json StaticActors = Save["StaticActors"];

    bool allSuccessful = true;

    LOG_DEFAULT(LogType::VITAL, "Loading static actors from persistent level");


    for (const auto& [ClassID, posList] : StaticActors.items()) {
        LOG_DEFAULT(LogType::INFO, fmt::format("Loading static actors of class: {}", ClassID));

        for (const auto& pos : posList) {
            
            if (!pos.is_array() || pos.size() != 2) {
                LOG_DEFAULT(LogType::WARNING, fmt::format("Invalid position data for class: {} - skipped loading", ClassID));
                continue;
            } 

            Vector2 Position;

            try {

                float x = pos[0].get<float>();
                float y = pos[1].get<float>();
                Position = Vector2(x,y);
                
            } catch (const json::type_error& e) {

                LOG_DEFAULT(LogType::WARNING, fmt::format("Failed to parse data for actor: {} - skipped loading", e.what()));
                allSuccessful = false;

                continue;
            }
            
            Archivable* obj = instantiateFromArchive(ClassID);

            // if returns nullptr, skip
            if (obj == nullptr) {
                allSuccessful = false;
                continue;
            }

            if (Actor* addedActor = GameInstance::get()->GetWorld()->AddtoPool(dynamic_cast<Actor*>(obj))) {
                addedActor->SetPosition(Position);
            } else {
                allSuccessful = false;
                LOG_DEFAULT(LogType::WARNING, fmt::format( "Failed to load static actor when adding to actor pool: {} - skipped loading", ClassID ));
                delete obj;
            }
        }

    }


    LOG_DEFAULT(LogType::VITAL, fmt::format("Static actors loaded {}", allSuccessful ? "successfully" : "unsuccessfully"));
    return allSuccessful;
}

int PersistentLevel::GetIntData( std::string key ) {
    json Save = safeGetJson(saveFileAbsPath);

    return Save["Data"][key].get<int>();
}
float PersistentLevel::GetFloatData( std::string key ) {
    json Save = safeGetJson(saveFileAbsPath);

    return Save["Data"][key].get<float>();
}
std::string PersistentLevel::GetStringData( std::string key ) {
    json Save = safeGetJson(saveFileAbsPath);

    return Save["Data"][key].get<std::string>();
}
Vector2 PersistentLevel::GetVector2Data( std::string key ) {
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

static json safeGetJson(const std::filesystem::path& path) {
    json parsed;

    if (!std::filesystem::exists(path)) {
        LOG_DEFAULT(LogType::ERROR, fmt::format("Save file not found at {}", path.c_str()));
        return parsed;
    }

    std::ifstream file(path);

    if (!file.is_open()) {
        LOG_DEFAULT(LogType::ERROR, fmt::format("Could not open save file at {}", path.c_str()));
        return parsed;
    }

    try {
        parsed = json::parse(file);
    } catch (const json::parse_error& e) {
        LOG_DEFAULT(LogType::ERROR, fmt::format("Failed to parse save file at {}: {}", path.c_str(), e.what()));   
    }

    return parsed;

} 

static Archivable* instantiateFromArchive(const std::string& ClassID) {

    auto& Archive = __Archive::_GetArchive();

    // if ClassID not found in archive, return nullptr to skip
    auto it = Archive.find(ClassID);
    if (it == Archive.end()) {
        LOG_DEFAULT(LogType::WARNING, fmt::format("Unkown ClassID in factory: {} - skipped loading", ClassID));
        return nullptr;
    }

    const std::function<Archivable*()>& constructor = it->second;
    if (constructor == nullptr) {
        LOG_DEFAULT(LogType::WARNING, fmt::format("Bad function reference in archive for class: {} - skipped loading", ClassID));
        return nullptr;
    }

    Archivable* obj = constructor();
    if (obj == nullptr) {
        LOG_DEFAULT(LogType::WARNING, fmt::format("Object could not be constructor for class: {} - skipped loading", ClassID));
        return nullptr;
    }
    
    return obj;

}





