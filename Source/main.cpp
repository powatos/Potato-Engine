
#include <iostream>

#include "Utils/Debug.h"
#include "Engine/GameInstance.h"
#include "Engine/Engine.h"
#include "Engine/Systems/IOController.h"

int main()
{
    std::cout << "Session Start\n";

    Debug::BindDebugLogs();

    // Initialize engine singletons
    [[maybe_unused]] Engine* engine = Engine::get();
    [[maybe_unused]] IOController* Controller = IOController::get();
    [[maybe_unused]] GameInstance* Instance = GameInstance::get();

    engine->main();

    // End of session

    return 0;    
}