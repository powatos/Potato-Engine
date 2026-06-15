
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

    /// PLAYER SETUP
    PlayerController* playerController = instance->GetPlayerController();
    Player* player = playerController->GetPlayer();
    player->SetPosition(Vector2(1, 1));

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


