
#include <memory>

#include "Core/PotatoEngine.hpp"
#include "Core/Datastore/PersistentLevel.hpp"
#include "Debug/Debug.hpp"
#include "Core/Event/EventController.hpp"
#include "Game/Control/GameInstance.hpp"
#include "Game/World.hpp"
#include "Game/Actors/Player.hpp"
#include "Util/Vector2.hpp"


int main()
{
    PotatoEngine& engine = PotatoEngine::Get();
    engine.LoadSubobjects();
    
    GameInstance* instance = GameInstance::get();
    
    PersistentLevel level("save.json");
    level.LoadStaticActors();

    PlayerController* playerController = instance->GetPlayerController();
    Player* player = playerController->GetPlayer();

    player->Texture = '0';

    engine.BeginPlay();

    engine.Resolve();

    return 0; 
}


