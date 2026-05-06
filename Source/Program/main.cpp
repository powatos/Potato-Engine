
#include <memory>

#include "Core/PotatoEngine.hpp"
#include "Core/Datastore/PersistentLevel.hpp"
#include "Debug/Debug.hpp"
#include "Core/Event/EventController.hpp"
#include "Game/Control/GameInstance.hpp"
#include "Game/World.hpp"
#include "Game/Actors/Player.hpp"
#include "Util/Vector2.hpp"
#include "Game/UI/HUDController.hpp"
#include "Game/UI/Widgets/Objects/DebugInfo.hpp"

// todo: make level rendering relative to player

int main()
{
    /// ENGINE SETUP
    PotatoEngine& engine = PotatoEngine::Get();
    engine.LoadSubobjects();
    GameInstance* instance = GameInstance::get();
    
    /// LEVEL SETUP
    PersistentLevel level("save.json");
    level.LoadStaticActors();

    /// PLAYER SETUP
    PlayerController* playerController = instance->GetPlayerController();
    Player* player = playerController->GetPlayer();

    player->Texture = '0';

    /// UI SETUP
    DebugInfo* debugInfoWidget = engine.GetHUDController()->AddWidget<DebugInfo>("W_DebugInfo");

    /// PLAY
    engine.BeginPlay();

    engine.Resolve();

    return 0; 
}


