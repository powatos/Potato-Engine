/** @file Gamemode.cpp */

#include "Core/Control/GameInstance.hpp"

#include "Debug/Debug.hpp"
#include "Util/TimerManager.hpp"

#include "Gamemode.hpp"

void Gamemode::BeginPlay() {
    LOG_DEFAULT(LogType::INFO, "Gamemode BeginPlay called");
    TimerManager::Get()->AddTimer("recordSecond", 1.0, this, &Gamemode::RecordSecond);

}

void Gamemode::RecordSecond() {
    LOG_DEFAULT(LogType::DEBUG, "sec");
    TimerManager::Get()->AddTimer("recordSecond1", 1.0, this, &Gamemode::RecordSecond);
}