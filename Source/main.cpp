
#include <iostream>

#include "Utils/Debug.h"

#include "Engine/PEngine.h"

int main()
{
    Debug::BindDebugLogs();

    // Initialize engine object
    [[maybe_unused]] PEngine* Engine = PEngine::get();

    Engine->Resolve();
    // End of session

    std::cout << "test\n";
    
    return 0;    
}