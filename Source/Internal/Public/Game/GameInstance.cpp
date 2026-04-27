
#include "World.hpp"
#include "Debug/Debug.hpp"

#include "GameInstance.hpp"

GameState::GameState() {

    isMainTickRunning = false;

}


[[maybe_unused]] GameInstance* GameInstance::get() {
    // constructed on first call
    static GameInstance instance;
    
    return &instance;
}

GameInstance::GameInstance() {
    LOG_DEFAULT(LogType::VITAL, "GameInstance constructed");
    
    state = GameState();
    world = new World();
}

void GameInstance::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving GameInstance");

    delete world;
}

GameInstance::~GameInstance() {
    LOG_DEFAULT(LogType::VITAL, "GameInstance destroying");
}
