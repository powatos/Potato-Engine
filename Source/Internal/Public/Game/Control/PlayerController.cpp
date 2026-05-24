/** @file PlayerController.cpp */

#include <algorithm>

#include "Game/Actors/Player.hpp"
#include "Game/Actors/Camera.hpp"
#include "Core/PotatoEngine.hpp"
#include "GameInstance.hpp"
#include "Game/World.hpp"
#include "Core/Input/InputController.hpp"
#include "Core/Event/EventController.hpp"
#include "Util/GameplayHelper.hpp"
#include "Debug/Debug.hpp"

#include "PlayerController.hpp"

SET_DEFAULT_SUBCLASS(PlayerController, PlayerController)

PlayerController::PlayerController() {

}

void PlayerController::Initialize() {

    World* world = GameInstance::get()->GetWorld();

    // Create camera
    ActiveCamera = world->SpawnActor<Camera>();

    SetTicking(true);
    TargetMovementVelocity = 1000.f;
    JumpForce = 20.f;

}

void PlayerController::Tick(float dt) {
    Tickable::Tick(dt);

    if (ActivePlayer == nullptr) { return; }

    Vector2 newCamPos = ActivePlayer->GetPosition();

    // camera x is median of player
    // camera y fills screen (top)

    newCamPos.x -= ActiveCamera->GetSize().x/2;
    newCamPos.y = ActiveCamera->GetSize().y-1;

    newCamPos.x = std::clamp(newCamPos.x, 0.f, 1000.f);

    ActiveCamera->SetPosition(newCamPos);

    ActivePlayer->AddForce(playerMoveVec * TargetMovementVelocity);

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
        InputBinding(Keycode::A, InputType::Triggered, "StartMoveLeft", this, &PlayerController::sMvL),
        InputBinding(Keycode::D, InputType::Triggered, "StartMoveRight", this, &PlayerController::sMvR),
        
        InputBinding(Keycode::Space, InputType::Impulse, "Jump", this, &PlayerController::jump),
        
        InputBinding(Keycode::A, InputType::Completed, "CompleteMoveLeft", this, &PlayerController::eMvL),
        InputBinding(Keycode::D, InputType::Completed, "CompleteMoveRight", this, &PlayerController::eMvR),
    });
}

#pragma region Move functions

void PlayerController::sMvL() { playerMoveVec.x = -1; }
void PlayerController::sMvR() { playerMoveVec.x =  1; }

void PlayerController::jump() { ActivePlayer->AddImpulse(Vector2(0, JumpForce)); }

void PlayerController::eMvL() { playerMoveVec.x = 0; }
void PlayerController::eMvR() { playerMoveVec.x = 0; }

#pragma endregion

PlayerController::~PlayerController() {
    PotatoEngine::Get().GetInputController()->UnregisterAllInputBindings(this);
}