
#include "Util/Vector2.h"
#include "Archivable.h"
#include "Game/GameInstance.h"
#include "Debug/Debug.h"
#include "Game/World.h"

#include "fmt/core.h"
#include "nlohmann/json.hpp"
#include "PersistentLevel.h"

using json = nlohmann::json;

static json safeGetJson(std::ifstream& savePath) {
    json parsed;

    try {
        parsed = json::parse(savePath);
    } catch (const json::parse_error& e) {
        LOG_DEFAULT(LogType::ERROR, fmt::format("Failed to parse save file: {}", e.what()));   
    }

    return parsed;

} 

PersistentLevel::PersistentLevel(std::ifstream& save) : savePath(save)
{
}


bool PersistentLevel::LoadStaticActors() {
    json Save = safeGetJson(savePath);

    json StaticActors = Save["StaticActors"];

    LOG_DEFAULT(LogType::INFO, fmt::format("Loading {} static actors", StaticActors.size()));

    bool allSuccessful = true;
    for (const auto& [ClassID, pos] : StaticActors.items()) {
        Vector2 Position;

        try {
            Position = Vector2(pos[0].get<float>(), pos[1].get<float>());
        } catch (const json::type_error& e) {
            LOG_DEFAULT(LogType::WARNING, fmt::format("Failed to parse data for actor: {}", e.what()));
            allSuccessful = false;

            continue;
        }

        Archivable* actor = _GetArchive()[ClassID]();

        if (Actor* addedActor = GameInstance::get()->GetWorld()->AddtoPool(dynamic_cast<Actor*>(actor))) {
            addedActor->SetPosition(Position);
        } else {
            allSuccessful = false;
            LOG_DEFAULT(LogType::WARNING, fmt::format( "Failed to load static actor when adding to actor pool: {}", ClassID ));
            delete actor;
        }

    }

    LOG_DEFAULT(LogType::INFO, fmt::format("Static actors loaded {}", allSuccessful ? "successfully" : "unsuccessfully"));
    return allSuccessful;
}

int PersistentLevel::GetIntData( std::string key ) {
    json Save = safeGetJson(savePath);

    return Save["Data"][key].get<int>();
}
float PersistentLevel::GetFloatData( std::string key ) {
    json Save = safeGetJson(savePath);

    return Save["Data"][key].get<float>();
}
std::string PersistentLevel::GetStringData( std::string key ) {
    json Save = safeGetJson(savePath);

    return Save["Data"][key].get<std::string>();
}
Vector2 PersistentLevel::GetVector2Data( std::string key ) {
    json Save = safeGetJson(savePath);

    json vecJson = Save["Data"][key];
    return Vector2(vecJson[0].get<float>(), vecJson[1].get<float>());
}

void PersistentLevel::WriteIntData( std::string key, int value ) {
    json Save = safeGetJson(savePath);

    Save["Data"][key] = value;
}
void PersistentLevel::WriteFloatData( std::string key, float value ) {
    json Save = safeGetJson(savePath);

    Save["Data"][key] = value;
}
void PersistentLevel::WriteStringData( std::string key, std::string value ) {
    json Save = safeGetJson(savePath);

    Save["Data"][key] = value;
}
void PersistentLevel::WriteVector2Data( std::string key, const Vector2& value ) {
    json Save = safeGetJson(savePath);

    Save["Data"][key] = { value.x, value.y };
}