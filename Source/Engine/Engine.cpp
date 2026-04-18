
#include "Engine.h"
#include "Utils/Debug.h"
#include "Engine/GameInstance.h"

#include <chrono>
#include <thread>

#include "Engine/Systems/IOController.h"

[[maybe_unused]] Engine* Engine::get() {
    // constructs on first call
    static Engine instance;
    
    return &instance;
}

Engine::Engine() {

    LOG_DEFAULT(LogType::VITAL, "Engine instantiated");

    GameInstance::get()->GetState().isMainTickRunning = true;
}

GameState& Engine::GetState() {
    return state;
}

void Engine::Resolve() noexcept {
    // engine class specific logic
    LOG_DEFAULT(LogType::VITAL, "Resolve called to Engine");

}

Engine::~Engine() {
    Resolve();

    LOG_DEFAULT(LogType::VITAL, "Engine Destroying");
}

/** 
* Main game loop
*/  
int Engine::main() {
    namespace stdc = std::chrono;
    using chronoUnit = stdc::milliseconds;

    LOG_DEFAULT(LogType::VITAL, "Engine game loop started");
    
    IOController* Controller = IOController::get();
    GameState& state = GameInstance::get()->GetState();

    const chronoUnit idealDelay = stdc::duration_cast<chronoUnit>( stdc::duration<double>(1.0 / Controller->FRAMES_PER_SECOND) );
    auto lastTick = stdc::steady_clock::now();

    while (state.isMainTickRunning == true) {
        Controller->HandleInput();

        Controller->Draw();

        // Syncronize FPS (dynamic sleep time based on variable tick times)
        // TODO: use accumulative smoothing instead of per-tick correction
        auto now = stdc::steady_clock::now();
        const chronoUnit chronoUnitElapsed = stdc::duration_cast<chronoUnit>(now - lastTick);
        const chronoUnit correctionDelay = std::max(chronoUnit(0), idealDelay - chronoUnitElapsed);
        
        lastTick = stdc::steady_clock::now();

        std::this_thread::sleep_for(correctionDelay);
    }
    
    LOG_DEFAULT(LogType::VITAL, "Engine self-resolving");

    return 0;
}