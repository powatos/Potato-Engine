
#include <iostream>

#include "Utils/Debug.h"

#include "Engine/Engine.h"

int main()
{
    std::cout << "Session Start\n";

    Debug::BindDebugLogs();

    // Initialize engine object
    [[maybe_unused]] Engine* engine = Engine::get();

    engine->Resolve();
    // End of session

    std::cout << "Session End\n";
    return 0;    
}