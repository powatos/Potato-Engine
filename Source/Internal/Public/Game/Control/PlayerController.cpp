/** @file PlayerController.cpp */

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
    if (ActivePlayer == nullptr) { return; }

    Vector2 newCamPos = ActivePlayer->GetPosition();

    // camera x is median of player
    // camera y fills screen (top)

    newCamPos.x -= ActiveCamera->GetSize().x/2;
    newCamPos.y = ActiveCamera->GetSize().y-1;

    ActiveCamera->SetPosition(newCamPos);

    ActivePlayer->AddLocalOffset(playerMoveVec * 0.5);

}

void PlayerController::sMvL() { playerMoveVec.x = -1; }
void PlayerController::sMvR() { playerMoveVec.x =  1; }
void PlayerController::sMvU() { playerMoveVec.y =  1; }
void PlayerController::sMvD() { playerMoveVec.y = -1; }

void PlayerController::eMvL() { playerMoveVec.x = 0; }
void PlayerController::eMvR() { playerMoveVec.x = 0; }
void PlayerController::eMvU() { playerMoveVec.y = 0; }
void PlayerController::eMvD() { playerMoveVec.y = 0; }


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
        InputBinding(Keycode::W, InputType::Triggered, "StartMoveUp", this, &PlayerController::sMvU),
        InputBinding(Keycode::S, InputType::Triggered, "StartMoveDown", this, &PlayerController::sMvD),
        
        InputBinding(Keycode::A, InputType::Completed, "CompleteMoveLeft", this, &PlayerController::eMvL),
        InputBinding(Keycode::D, InputType::Completed, "CompleteMoveRight", this, &PlayerController::eMvR),
        InputBinding(Keycode::W, InputType::Completed, "CompleteMoveUp", this, &PlayerController::eMvU),
        InputBinding(Keycode::S, InputType::Completed, "CompleteMoveDown", this, &PlayerController::eMvD)
    });
}

PlayerController::~PlayerController() {
    PotatoEngine::Get().GetInputController()->UnregisterAllInputBindings(this);
}