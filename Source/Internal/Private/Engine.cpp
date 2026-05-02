
#include <chrono>
#include <thread>
#include <immintrin.h>

#include "Debug/Debug.hpp"
#include "Game/Control/GameInstance.hpp"
#include "Systems/IOController.hpp"

#include "Engine.hpp"

[[maybe_unused]] Engine* Engine::get() {
    static Engine instance;
    
    return &instance;
}

Engine::Engine() {

    LOG_DEFAULT(LogType::VITAL, "Engine constructed");

}

int Engine::main() {
    namespace stdc = std::chrono;
    using ms = stdc::milliseconds;

    LOG_DEFAULT(LogType::VITAL, "Engine main loop started");
    
    IOController* Controller = IOController::get();
    GameInstance* Instance = GameInstance::get();

    Instance->isMainTickRunning = true;

    const ms idealDelay(static_cast<int>(1000.f / Controller->FRAMES_PER_SECOND));

    auto lastTick = stdc::steady_clock::now();

    while (Instance->isMainTickRunning == true) {
        auto currentTick = stdc::steady_clock::now();

        const stdc::duration<float> elapsed = currentTick - lastTick;
        lastTick = currentTick;

        float dt = elapsed.count();

        if (dt >= 0.5f) { dt = 0.5f; } // clamp max dt

        Controller->HandleInput();
        FireTick(dt);
        Controller->Draw();

        auto end = stdc::steady_clock::now();
        auto tickDuration = stdc::duration_cast<ms>(end - currentTick);

        if (tickDuration >= idealDelay) { continue; } // no sleep if passed ideal tick time

        const auto correctionDelay = idealDelay - tickDuration;
        // account for sleep latency (only sleep if buffer is larger than 2ms)
        // if (correctionDelay > ms(2)){
        //     std::this_thread::sleep_for(correctionDelay - ms(1));
        // }

        // // spin cpu while waiting for delay to be reached
        // while (stdc::steady_clock::now() - currentTick < idealDelay) {
        //     #if defined(__x86_64__) || defined(__M_X64)
        //         _mm_pause();
        //     #endif    
        // }
        std::this_thread::sleep_for(correctionDelay);
        
    }
    
    LOG_DEFAULT(LogType::VITAL, "Engine main loop finished");

    return 0;
}

void Engine::RegisterTick(EventDelegate<float> delegate) {
    // TODO: check if matching delegate already exists (only one delegate per instance allowed for tick binding)
    TickDelegates.push_back(delegate);
}

void Engine::UnregisterTick(void *object) {

    TickDelegates.erase(
        std::remove_if(TickDelegates.begin(), TickDelegates.end(), [object](const EventDelegate<float>& delegate){
            return delegate.GetInstance() == object;
        }),

        TickDelegates.end()
    );
    
}

void Engine::FireTick(const float dt) const {

    for (const EventDelegate<float>& delegate : TickDelegates) {
        delegate.Fire(dt);
    }

}


void Engine::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving Engine");
}

Engine::~Engine() {
    LOG_DEFAULT(LogType::VITAL, "Engine Destroying");
}