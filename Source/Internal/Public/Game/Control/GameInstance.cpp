
#include "Game/World.hpp"
#include "Debug/Debug.hpp"

#include "GameInstance.hpp"

[[maybe_unused]] GameInstance* GameInstance::get() {
    // constructed on first call
    static GameInstance instance;
    
    return &instance;
}

GameInstance::GameInstance() {
    LOG_DEFAULT(LogType::VITAL, "GameInstance constructed");
    
    isMainTickRunning = false;

    world = new World();

    if (DEFAULT_INSTANTIATORS::get_PlayerController() == nullptr) {
        LOG_DEFAULT(LogType::ERROR, "No PlayerController default instantiator on GameInstance");
    } else { 
        ActivePlayerController = DEFAULT_INSTANTIATORS::get_PlayerController()();
    }

    if (DEFAULT_INSTANTIATORS::get_Player() == nullptr) {
        LOG_DEFAULT(LogType::ERROR, "No Player default instantiator on GameInstance");
    } else {
        Player* p = DEFAULT_INSTANTIATORS::get_Player()();
        world->AddtoPool(p);
        ActivePlayerController->AssignPlayer(p);
    }
}

void GameInstance::LoadSubobjects() {
    ActivePlayerController->SetupInputBindings();
}

World* GameInstance::GetWorld() const { return world; }
PlayerController* GameInstance::GetPlayerController() const { return ActivePlayerController; }

void GameInstance::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving GameInstance");

    delete ActivePlayerController;
    delete world;
}

GameInstance::~GameInstance() {
    LOG_DEFAULT(LogType::VITAL, "GameInstance destroying");
}
