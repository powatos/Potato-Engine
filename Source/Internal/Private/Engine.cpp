
#include <chrono>
#include <thread>

#include "Debug/Debug.hpp"
#include "Game/GameInstance.hpp"
#include "Systems/IOController.hpp"

#include "Engine.hpp"


[[maybe_unused]] Engine* Engine::get() {
    static Engine instance;
    
    return &instance;
}


Engine::Engine() {

    LOG_DEFAULT(LogType::VITAL, "Engine constructed");

}

void Engine::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving Engine");
}

Engine::~Engine() {
    LOG_DEFAULT(LogType::VITAL, "Engine Destroying");
}

/** 
* Main game loop
*/  
int Engine::main() {
    namespace stdc = std::chrono;
    using chronoUnit = stdc::milliseconds;

    LOG_DEFAULT(LogType::VITAL, "Engine main loop started");
    
    IOController* Controller = IOController::get();
    GameInstance* Instance = GameInstance::get();
    GameState& state = Instance->GetState();

    state.isMainTickRunning = true;

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
    
    LOG_DEFAULT(LogType::VITAL, "Engine main loop finished");

    return 0;
}