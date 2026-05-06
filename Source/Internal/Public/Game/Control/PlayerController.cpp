
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

void PlayerController::MoveLeft() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(Vector2(-1, 0)); // Move left by 1 unit
}
void PlayerController::MoveRight() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(Vector2(1, 0)); // Move right by 1 unit
}
void PlayerController::MoveUp() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(Vector2(0, 1)); // Move left by 1 unit
}
void PlayerController::MoveDown() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(Vector2(0, -1)); // Move left by 1 unit
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

    controller->RegisterInputBinding( InputBinding(Keycode::A, "MoveLeft", this, &PlayerController::MoveLeft) );
    controller->RegisterInputBinding( InputBinding(Keycode::D, "MoveRight", this, &PlayerController::MoveRight) );
    controller->RegisterInputBinding( InputBinding(Keycode::W, "MoveUp", this, &PlayerController::MoveUp) );
    controller->RegisterInputBinding( InputBinding(Keycode::S, "MoveDown", this, &PlayerController::MoveDown) );
}

PlayerController::~PlayerController() {
    PotatoEngine::Get().GetInputController()->UnregisterAllInputBindings(this);
}