
#include "Game/Actors/Player.hpp"
#include "Game/Actors/Camera.hpp"
#include "Core/PotatoEngine.hpp"
#include "GameInstance.hpp"
#include "Game/World.hpp"
#include "Core/Input/InputController.hpp"
#include "Util/GameplayHelper.hpp"
#include "Debug/Debug.hpp"

#include "PlayerController.hpp"

SET_DEFAULT_SUBCLASS(PlayerController, PlayerController);

PlayerController::PlayerController() {

}

void PlayerController::Initialize() {

    World* world = GameInstance::get()->GetWorld();

    // Create camera
    ActiveCamera = world->SpawnActor<Camera>();

    SetTicking(true);
}

void PlayerController::Tick(float dt) {

    Vector2 newCamPos = ActivePlayer->GetPosition();

    // camera x is median of player
    // camera y fills screen (top)

    newCamPos.x -= ActiveCamera->GetSize().x/2;
    newCamPos.y = ActiveCamera->GetSize().y-1;

    ActiveCamera->SetPosition(newCamPos);

}

void PlayerController::sMvL() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(Vector2(-1.0, 0.0)); // Move left by 1 unit
}
void PlayerController::sMvR() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(Vector2(1.0, 0.0)); // Move right by 1 unit
}
void PlayerController::sMvU() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(Vector2(0.0, 1.0)); // Move left by 1 unit
}
void PlayerController::sMvD() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(Vector2(0.0, -1.0)); // Move left by 1 unit
}

void PlayerController::AssignPlayer(Player* player) {
    ActivePlayer = player;
    if (ActivePlayer == nullptr) {
        LOG_DEFAULT(LogType::WARNING, "Player set to nullptr during controller assignment");
    }
}

Player* PlayerController::GetPlayer() const { return ActivePlayer; }
Camera* PlayerController::GetCamera() const { return ActiveCamera; }

void PlayerController::SetupInputBindings() {

    // setup input bindings
    IInputController* controller = PotatoEngine::Get().GetInputController();

    controller->RegisterInputBinding({
            InputBinding(Keycode::A, InputType::Triggered, "StartMoveLeftK", this, &PlayerController::sMvL),
            InputBinding(Keycode::D, InputType::Triggered, "StartMoveRightK", this, &PlayerController::sMvR),
            InputBinding(Keycode::W, InputType::Triggered, "StartMoveUpK", this, &PlayerController::sMvU),
            InputBinding(Keycode::S, InputType::Triggered, "StartMoveDownK", this, &PlayerController::sMvD),
            
            InputBinding(Keycode::ArrowLeft, InputType::Triggered, "StartMoveLeftA", this, &PlayerController::sMvL),
            InputBinding(Keycode::ArrowRight, InputType::Triggered, "StartMoveRightA", this, &PlayerController::sMvR),
            InputBinding(Keycode::ArrowUp, InputType::Triggered, "StartMoveUpA", this, &PlayerController::sMvU),
            InputBinding(Keycode::ArrowDown, InputType::Triggered, "StartMoveDownA", this, &PlayerController::sMvD)
        });
}

PlayerController::~PlayerController() {
    PotatoEngine::Get().GetInputController()->UnregisterAllInputBindings(this);
}