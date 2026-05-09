
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

    SubsystemStack.push_back( Engine::get() );
    SubsystemStack.push_back( IOController::get() );
    SubsystemStack.push_back( UIController::get() );
    SubsystemStack.push_back( GameInstance::get() );

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

    for (IEngineSubsystem* sys : SubsystemStack) {
        sys->_BeginPlay();
    }

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

    for (auto it = SubsystemStack.end(); it != SubsystemStack.begin(); ) {
        --it;
        (*it)->Resolve();
        SubsystemStack.erase(it);
    }

}


PotatoEngine::~PotatoEngine() {
    LOG_DEFAULT(LogType::VITAL, "PotatoEngine destroying");
}
