
#include "Debug/Debug.h"
#include "Game/GameInstance.h"
#include "Engine.h"
#include "Core/EventController.h"
#include "Systems/IOController.h"

#include "Core/PotatoEngine.h"

PotatoEngine::PotatoEngine() {
    Impl = std::make_unique<InitImpl>();
}

PotatoEngine::~PotatoEngine() = default;

struct PotatoEngine::InitImpl {};

void PotatoEngine::Initialize()
{
    // Start of session

    Debug::BindDebugLogs();

    Engine::get();
    InputController = IOController::get();;
    GameInstance::get();

}

void PotatoEngine::BeginPlay()
{
    [[maybe_unused]] Engine* engine = Engine::get();

    engine->main();
}

IEventController* PotatoEngine::GetInputController() const {
    return InputController;
}