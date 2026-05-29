/** @file PotatoEngine.cpp */
#include "Core/Control/GameInstance.hpp"
#include "Core/Control/Gamemode.hpp"
#include "Core/Event/EventController.hpp"
#include "Engine.hpp"
#include "Game/World.hpp"
#include "Systems/IOController.hpp"
#include "Systems/UIController.hpp"
#include "UI/HUDController.hpp"

#include "Debug/Debug.hpp"

#include "Core/PotatoEngine.hpp"

PotatoEngine::PotatoEngine() {
    LOG_DEFAULT(LogType::VITAL, "PotatoEngine constructed");

    Debug::BindDebugLogs();

    SubsystemStack.push_back( Engine::Get() );
    SubsystemStack.push_back( IOController::Get() );
    SubsystemStack.push_back( UIController::Get() );
    SubsystemStack.push_back( GameInstance::Get() );
    SubsystemStack.push_back( EventController::Get() );

}

PotatoEngine& PotatoEngine::Get()
{
    static PotatoEngine engine;
    return engine;
}

void PotatoEngine::LoadSubobjects() {
    InputController = IOController::Get();
    HUDController = UIController::Get();
    NativeEventController = EventController::Get();

    GameInstance::Get()->LoadSubobjects();
}

void PotatoEngine::BeginPlay()
{
    Engine* engine = Engine::Get();
    GameInstance* instance = GameInstance::Get();
    World* world = instance->GetWorld();

    for (IEngineSubsystem* sys : SubsystemStack) {
        sys->_BeginPlay();
    }

    world->_BeginPlay();

    for (Actor* actor : world->GetAllActors()) {
        actor->DispatchBeginPlay();
    }

    instance->GetGamemode()->BeginPlay();

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

    for (auto it = SubsystemStack.end(); it != SubsystemStack.begin(); ) {
        --it;
        (*it)->Resolve();
        SubsystemStack.erase(it);
    }

    LOG_DEFAULT(LogType::VITAL, "Subsystem stack resolved");
}


PotatoEngine::~PotatoEngine() {
    LOG_DEFAULT(LogType::VITAL, "PotatoEngine destroying");
}
