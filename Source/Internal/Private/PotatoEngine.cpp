/** @file PotatoEngine.cpp */

#include "Debug/Debug.hpp"
#include "Core/Control/GameInstance.hpp"
#include "Core/Control/Gamemode.hpp"
#include "Engine.hpp"
#include "Core/Event/EventController.hpp"
#include "Systems/IOController.hpp"
#include "Systems/UIController.hpp"
#include "UI/HUDController.hpp"
#include "Game/World.hpp"

#include "Core/PotatoEngine.hpp"

PotatoEngine::PotatoEngine() {
    LOG_DEFAULT(LogType::VITAL, "PotatoEngine constructed");

    Debug::BindDebugLogs();

    SubsystemStack.push_back( Engine::get() );
    SubsystemStack.push_back( IOController::get() );
    SubsystemStack.push_back( UIController::get() );
    SubsystemStack.push_back( GameInstance::get() );
    SubsystemStack.push_back( EventController::get() );

}

PotatoEngine& PotatoEngine::Get()
{
    static PotatoEngine engine;
    return engine;
}

void PotatoEngine::LoadSubobjects() {
    InputController = IOController::get();
    HUDController = UIController::get();
    NativeEventController = EventController::get();

    GameInstance::get()->LoadSubobjects();
}

void PotatoEngine::BeginPlay()
{
    Engine* engine = Engine::get();
    GameInstance* instance = GameInstance::get();
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
