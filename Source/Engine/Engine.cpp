
#include "Engine.h"
#include "Utils/Debug.h"

#include "Engine/Systems/IOController.h"

[[maybe_unused]] Engine* Engine::get() {
    // constructs on first call
    static Engine instance;
    
    return &instance;
}



Engine::Engine() {

    LOG_DEFAULT(LogType::VITAL, "Engine instantiated");

    
    // IOManager cnstruction inits ncurses
    [[maybe_unused]] IOController* Controller = IOController::get();
    
    
}

void Engine::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolve called to Engine");


    IOController* Controller = IOController::get();
    Controller->Resolve();
}

Engine::~Engine() {
    Resolve();

    LOG_DEFAULT(LogType::VITAL, "SESSION TERMINATED");
}

/** 
* Main game loop
*/
int Engine::main() {

    LOG_DEFAULT(LogType::VITAL, "Engine game loop started");
    
    IOController* Controller = IOController::get();
    
    Controller->HandleInput();
    
    
    Controller->OutputDefault();
    
    LOG_DEFAULT(LogType::VITAL, "Engine game loop returning");
    return 0;
}