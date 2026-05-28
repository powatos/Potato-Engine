
#include <memory>

#include <Core/PotatoEngine.hpp>
#include <Core/Data/PersistentLevel.hpp>
#include <Debug/Debug.hpp>
#include <Core/Event/EventController.hpp>
#include <Game/Control/GameInstance.hpp>
#include <Game/World.hpp>
#include <Game/Actors/Player.hpp>
#include <Util/Vector2.hpp>
#include <UI/HUDController.hpp>
#include <Core/Input/InputController.hpp>
#include <UI/Widgets/Objects/DebugInfo.hpp>
#include <Game/Actors/Block.hpp>


void t() {
    LOG_DEFAULT(LogType::INFO, "e triggered");
}
void o() {
    LOG_DEFAULT(LogType::INFO, "e ongoing");
}
void c() {
    LOG_DEFAULT(LogType::INFO, "e ended");
}
// todo: update all docs

int main()
{
    /// ENGINE SETUP
    PotatoEngine& engine = PotatoEngine::Get();
    engine.LoadSubobjects();
    GameInstance* instance = GameInstance::get();
    
    // ideal 195
    instance->MS_REPEAT_THRESHOLD = 195;
    instance->FRAMES_PER_SECOND = 60.f;

    /// LEVEL SETUP
    [[maybe_unused]] World* world = instance->GetWorld();
    PersistentLevel level("save1.json");
    level.LoadStaticActors();

    /// PLAYER SETUP
    PlayerController* playerController = instance->GetPlayerController();
    Player* player = playerController->GetPlayer();
    player->SetPosition(Vector2(0, 1.5));

    player->Texture = '0';
    player->AddImpulse(Vector2(-1, 0));

    /// UI SETUP
    [[maybe_unused]] IHUDController* HUDController = engine.GetHUDController();

    /// DEBUG
    [[maybe_unused]] DebugInfo *debugInfoWidget = HUDController->AddWidget<DebugInfo>("W_DebugInfo");

    /// PLAY
    engine.BeginPlay();

    engine.Resolve();

    return 0; 
}


