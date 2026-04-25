
#include "Core/PotatoEngine.h"

#include "Core/Datastore/PersistentLevel.h"
#include "Debug/Debug.h"
#include "Core/EventController.h"

#include <fstream>

int main()
{
    PotatoEngine engine;
    std::ifstream saveFile;
    saveFile.open("save.json");
    PersistentLevel level(saveFile);

    engine.Initialize();
    level.LoadStaticActors();

    engine.GetInputController()->RegisterInputBinding('W', []() {
        LOG_DEFAULT(LogType::INFO, "W pressed");
    });

    engine.BeginPlay();

    return 0; 
}


