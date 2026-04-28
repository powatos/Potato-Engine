
#include "Debug/Debug.hpp"
#include "Game/GameInstance.hpp"
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

    InputController = IOController::get();
    EventController = InputController;

}

PotatoEngine::~PotatoEngine() {
    LOG_DEFAULT(LogType::VITAL, "PotatoEngine destroying");
}

PotatoEngine& PotatoEngine::Get()
{
    static PotatoEngine engine;
    return engine;
}

void PotatoEngine::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving PotatoEngine");

    while (!SubsystemStack.empty()) {
        IEngineSubsystem* sys = SubsystemStack.top();
        sys->Resolve();
        // delete sys;

        SubsystemStack.pop();
    }

}

void PotatoEngine::BeginPlay()
{
    [[maybe_unused]] Engine* engine = Engine::get();

    engine->main();
}

IInputController* PotatoEngine::GetInputController() const {
    return InputController;
}

IEventController* PotatoEngine::GetEventController() const {
    return EventController;
}