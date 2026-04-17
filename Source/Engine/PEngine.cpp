
#include "PEngine.h"
#include "Utils/Debug.h"

#include "Engine/Systems/PIOController.h"

[[maybe_unused]] PEngine* PEngine::get() {
    // constructs on first call
    static PEngine instance;
    
    return &instance;
}



PEngine::PEngine() {

    LOG_DEFAULT(LogType::VITAL, "Engine instantiated");

    
    // IOManager cnstruction inits ncurses
    [[maybe_unused]] PIOController* IOController = PIOController::get();
    
    
}

void PEngine::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolve called to Engine");


    PIOController* IOController = PIOController::get();
    IOController->Resolve();
}

PEngine::~PEngine() {
    Resolve();

    LOG_DEFAULT(LogType::VITAL, "SESSION TERMINATED");
}

/** 
* Main game loop
*/
int PEngine::main() {

    LOG_DEFAULT(LogType::VITAL, "Engine game loop started");
    
    PIOController* IOController = PIOController::get();
    
    IOController->HandleInput();
    
    
    IOController->OutputDefault();
    
    LOG_DEFAULT(LogType::VITAL, "Engine game loop returning");
    return 0;
}