
#include <memory>

#include "Core/PotatoEngine.hpp"
#include "Core/Datastore/PersistentLevel.hpp"
#include "Debug/Debug.hpp"
#include "Core/EventController.hpp"
#include "Game/GameInstance.hpp"
#include "Game/World.hpp"
#include "Game/Actors/Player.hpp"
#include "Util/Vector2.hpp"


int main()
{
    PotatoEngine& engine = PotatoEngine::Get();
    
    PersistentLevel level("save.json");
    level.LoadStaticActors();

    Player* player = GameInstance::get()->GetWorld()->SpawnActor<Player>(Vector2(1,1));
    player->Texture = 'P';

    engine.BeginPlay();

    engine.Resolve();

    return 0; 
}


