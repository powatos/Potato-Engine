
#include "Debug/Debug.hpp"
#include "Game/Control/GameInstance.hpp"
#include "Engine.hpp"
#include "Core/Event/EventController.hpp"
#include "Systems/IOController.hpp"

#include "Core/PotatoEngine.hpp"

PotatoEngine::PotatoEngine() {
    LOG_DEFAULT(LogType::VITAL, "PotatoEngine constructed");

    Debug::BindDebugLogs();

    SubsystemStack.push( Engine::get() );
    SubsystemStack.push( IOController::get() );
    SubsystemStack.push( GameInstance::get() );

    

}

PotatoEngine& PotatoEngine::Get()
{
    static PotatoEngine engine;
    return engine;
}

void PotatoEngine::LoadSubobjects() {
    InputController = IOController::get();
    EventController = InputController;

    GameInstance::get()->LoadSubobjects();
}

void PotatoEngine::BeginPlay()
{
    Engine* engine = Engine::get();

    engine->main();
}

IInputController* PotatoEngine::GetInputController() const {
    return InputController;
}

IEventController* PotatoEngine::GetEventController() const {
    return EventController;
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
