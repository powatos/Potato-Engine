
#include "Debug/Debug.hpp"
#include "Game/Control/GameInstance.hpp"
#include "Engine.hpp"
#include "Core/Event/EventController.hpp"
#include "Systems/IOController.hpp"
#include "Systems/UIController.hpp"
#include "Game/UI/HUDController.hpp"
#include "Game/World.hpp"

#include "Core/PotatoEngine.hpp"

PotatoEngine::PotatoEngine() {
    LOG_DEFAULT(LogType::VITAL, "PotatoEngine constructed");

    Debug::BindDebugLogs();

    SubsystemStack.push( Engine::get() );
    SubsystemStack.push( IOController::get() );
    SubsystemStack.push( UIController::get() );
    SubsystemStack.push( GameInstance::get() );

}

PotatoEngine& PotatoEngine::Get()
{
    static PotatoEngine engine;
    return engine;
}

void PotatoEngine::LoadSubobjects() {
    InputController = IOController::get();
    TickController = Engine::get();
    HUDController = UIController::get();

    GameInstance::get()->LoadSubobjects();
}

void PotatoEngine::BeginPlay()
{
    Engine* engine = Engine::get();

    // call BeginPlay on all actors
    // TODO: put somewhere else more reasonable
    for (Actor* actor : GameInstance::get()->GetWorld()->GetAllActors()) {
        actor->DispatchBeginPlay();
    }


    engine->main();
}

IInputController* PotatoEngine::GetInputController() const {
    return InputController;
}

ITickController* PotatoEngine::GetTickController() const {
    return TickController;
}

IHUDController* PotatoEngine::GetHUDController() const {
    return HUDController;
}

void PotatoEngine::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving PotatoEngine (Subsystem stack resolve)");

    while (!SubsystemStack.empty()) {
        IEngineSubsystem* sys = SubsystemStack.top();
        sys->Resolve();
        SubsystemStack.pop();
    }

}


PotatoEngine::~PotatoEngine() {
    LOG_DEFAULT(LogType::VITAL, "PotatoEngine destroying");
}
