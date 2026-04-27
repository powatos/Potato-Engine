
#include <memory>

#include "Core/PotatoEngine.hpp"
#include "Core/Datastore/PersistentLevel.hpp"
#include "Debug/Debug.hpp"
#include "Core/EventController.hpp"
#include "Game/GameInstance.hpp"
#include "Game/World.hpp"
#include "Game/Actors/Player.hpp"


int main()
{
    PotatoEngine& engine = PotatoEngine::Get();
    
    PersistentLevel level("save.json");
    level.LoadStaticActors();

    GameInstance::get()->GetWorld()->SpawnActor<Player>();

    engine.BeginPlay();

    engine.Resolve();

    return 0; 
}


