/** @file PotatoEngine.cpp */

#include <stdio.h>
#include <cstdlib>

#include "Core/Control/GameInstance.hpp"
#include "Core/Control/Gamemode.hpp"
#include "Core/Event/EventController.hpp"
#include "Engine.hpp"
#include "Game/World/World.hpp"
#include "Systems/IOController.hpp"
#include "Systems/UIController.hpp"
#include "Core/Textures/TextureManager.hpp"
#include "Core/Control/GameInstance.hpp"
#include "UI/HUDController.hpp"
#include "Core/Tick/TickController.hpp"
#include "Systems/PhysicsController.hpp"
#include "Core/Input/InputController.hpp"
#include "Util/TimerManager.hpp"

#include "Debug/Log.hpp"

#include "Core/PotatoEngine.hpp"

void clearConsole();

PotatoEngine::PotatoEngine() {
    startup();

    DebugLogs::BindDebugLogs();

    LOG_DEFAULT(LogType::VITAL, "PotatoEngine constructed");

    SubsystemStack.push_back( Engine::Get() );

    SubsystemStack.push_back( TickController::Get() );

    SubsystemStack.push_back( IOController::Get() );

    SubsystemStack.push_back( TextureManager::Get() );

    SubsystemStack.push_back( GameInstance::Get() );

    SubsystemStack.push_back( EventController::Get() );
        
    SubsystemStack.push_back( PhysicsController::Get() );

    SubsystemStack.push_back( UIController::Get() );
    SubsystemStack.push_back( TimerManager::Get() );

}

PotatoEngine& PotatoEngine::Get()
{
    static PotatoEngine engine;
    return engine;
}

void PotatoEngine::startup() {
    clearConsole();

    printf("> POTATO ENGINE by @powatos\n");
}

void PotatoEngine::LoadSubclasses() {
    InputController = IOController::Get();
    HUDController = UIController::Get();
    NativeEventController = EventController::Get();

    GameInstance::Get()->LoadSubclasses();
}

void PotatoEngine::BeginPlay()
{
    Engine* engine = Engine::Get();

    // Bind exit key (intentional lambda to surpress unregisters)
    InputController->RegisterInputBinding(InputBinding(
        Keycode::Escape, 
        InputType::Impulse, 
        "ExitGame", 
        []() { GameInstance::Get()->RequestShutdown(); }
    ));

    // Dispatch on subsystems
    for (IEngineSubsystem* sys : SubsystemStack) {
        sys->BeginPlay();
    }

    // Begin game loop
    engine->main();
}

IInputController* PotatoEngine::GetInputController() const {
    return InputController;
}

IHUDController* PotatoEngine::GetHUDController() const {
    return HUDController;
}

EventController* PotatoEngine::GetNativeEventController() const {
    return NativeEventController;
}


void PotatoEngine::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving PotatoEngine (Subsystem stack resolve)");

    while (!SubsystemStack.empty()) {
        SubsystemStack.back()->Resolve();
        SubsystemStack.pop_back();
    }

    clearConsole();
    LOG_DEFAULT(LogType::VITAL, "Subsystem stack resolved");
}


PotatoEngine::~PotatoEngine() {
    LOG_DEFAULT(LogType::VITAL, "PotatoEngine destroying");
}


void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::system("clear");
#endif
}