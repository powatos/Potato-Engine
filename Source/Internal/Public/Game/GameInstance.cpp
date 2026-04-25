
#include "World.h"

#include "GameInstance.h"

GameState::GameState() {

    isMainTickRunning = false;

}


[[maybe_unused]] GameInstance* GameInstance::get() {
    // constructed on first call
    static GameInstance instance;
    
    return &instance;
}

GameInstance::GameInstance() {
    // LOG_DEFAULT(LogType::VITAL, "GameInstance instantiated");
    
    state = GameState();
    world = new World();
}

GameInstance::~GameInstance() {
    // LOG_DEFAULT(LogType::VITAL, "GameInstance destroying");
    
    delete world;
}
