/** @file GameInstance.cpp */

#include "Core/Control/Gamemode.hpp"
#include "Game/Actors/Player.hpp"
#include "Game/World.hpp"

#include "Debug/Debug.hpp"

#include "GameInstance.hpp"

GameInstance::GameInstance() {
    LOG_DEFAULT(LogType::VITAL, "GameInstance constructed");
    
    _isMainTickRunning = false;
    FRAMES_PER_SECOND = 24.f;
    MS_REPEAT_THRESHOLD = 250;

    world = new World();

    InstantiateSubclasses();
}

void GameInstance::InstantiateSubclasses() {

    // User-defined Instantiaters
    auto c_pc = __DEFAULT_INSTANTIATORS::_PlayerController();
    auto c_p = __DEFAULT_INSTANTIATORS::_Player();
    auto c_gm = __DEFAULT_INSTANTIATORS::_Gamemode();
    
    // PlayerController
    if (c_pc == nullptr) {
        LOG_DEFAULT(LogType::WARNING, "No PlayerController default instantiator on GameInstance. Fallback to engine default.");
        ActivePlayerController = new PlayerController();
    } else { 
        ActivePlayerController = c_pc();
    }

    // Player
    Player* player;
    if (c_p == nullptr) {
        LOG_DEFAULT(LogType::WARNING, "No Player default instantiator on GameInstance. Fallback to engine default.");
        player = new Player();
    } else {
        player = c_p();
    }
    world->AddtoPool(player);
    ActivePlayerController->AssignPlayer(player);

    // Gamemode
    if (c_gm == nullptr) {
        LOG_DEFAULT(LogType::WARNING, "No Gamemode default instantiator on GameInstance. Fallback to engine default.");
        ActiveGamemode = new Gamemode();
    } else {
        ActiveGamemode = c_gm();
    }

}

void GameInstance::RequestShutdown() {
    _isMainTickRunning = false;
}

void GameInstance::LoadSubclasses() {
    ActivePlayerController->Initialize();
    ActivePlayerController->SetupInputBindings();
}

World* GameInstance::GetWorld() const { return world; }
PlayerController* GameInstance::GetPlayerController() const { return ActivePlayerController; }
Gamemode* GameInstance::GetGamemode() const { return ActiveGamemode; }

void GameInstance::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving GameInstance");

    delete ActivePlayerController;
    delete world;
}

GameInstance::~GameInstance() {
    LOG_DEFAULT(LogType::VITAL, "GameInstance destroying");
}
