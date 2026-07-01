
#include <Core/Control/GameInstance.hpp>
#include <Core/Data/PersistentLevel.hpp>
#include <Core/Event/EventController.hpp>
#include <Core/Input/InputController.hpp>
#include <Core/PotatoEngine.hpp>
#include <Game/Actors/Block.hpp>
#include <Game/Actors/Player.hpp>
#include <Game/World/World.hpp>
#include <UI/HUDController.hpp>
#include <UI/Widgets/Objects/DebugInfo.hpp>
#include <Core/Textures/TextureManager.hpp>
#include <Core/Textures/Texture.hpp>

#include <Debug/Debug.hpp>
#include <Util/Vector2.hpp>

#include <memory>

int main()
{
    /// ENGINE SETUP
    PotatoEngine& engine = PotatoEngine::Get();
    engine.LoadSubclasses();
    GameInstance* instance = GameInstance::Get();
    
    // ideal 195
    instance->MS_REPEAT_THRESHOLD = 195;
    instance->FRAMES_PER_SECOND = 60.f;

    /// LEVEL SETUP
    [[maybe_unused]] World* world = instance->GetWorld();
    PersistentLevel level("save1.json");
    level.LoadStaticActors();

    Block* Obstacle1 = world->SpawnActor<Block>(Vector2(10,2));
    Obstacle1->SetSize(Vector2(5, 3));
    Obstacle1->ctex = 'O';
    Obstacle1->SetCollisionType(CollisionType::Overlap);

    /// PLAYER SETUP
    PlayerController* playerController = instance->GetPlayerController();
    Player* player = playerController->GetPlayer();
    player->SetPosition(Vector2(0, 5));
    player->GetTexture().SetRotation(0.f);
    player->SetUsingCTex(true);
    player->SetSize(Vector2(5,2));
    player->ctex = 'P';

    /// UI SETUP
    [[maybe_unused]] IHUDController* HUDController = engine.GetHUDController();

    /// DEBUG
    [[maybe_unused]] DebugInfo* debugInfoWidget = HUDController->AddWidget<DebugInfo>("W_DebugInfo");
    engine.GetInputController()->RegisterInputBinding(InputBinding(
        Keycode::T, 
        InputType::Impulse, 
        "ToggleDebugInfo", 
        static_cast<UIElement*>(debugInfoWidget), 
        &DebugInfo::ToggleVisibility
    ));

    /// PLAY
    engine.BeginPlay();

    engine.Resolve();

    return 0; 
}


