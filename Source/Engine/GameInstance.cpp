#pragma once

#include "GameInstance.h"

[[maybe_unused]] GameInstance* GameInstance::get() {
    // constructed on first call
    static GameInstance instance;
    
    return &instance;
}

GameState::GameState() {

    isMainTickRunning = false;

}

GameInstance::GameInstance() {
    // LOG_DEFAULT(LogType::VITAL, "GameInstance instantiated");
    
    state = GameState();
}

GameInstance::~GameInstance() {
    // LOG_DEFAULT(LogType::VITAL, "GameInstance destroying");
}
