
#include <memory>

#include "Core/PotatoEngine.h"
#include "Core/Datastore/PersistentLevel.h"
#include "Debug/Debug.h"
#include "Core/EventController.h"

#include "Game/Player.h"

int main()
{
    PotatoEngine engine;
    PersistentLevel level("save.json");

    engine.Initialize();
    level.LoadStaticActors();

    engine.BeginPlay();

    return 0; 
}


