
#include "Game/Actors/Player.hpp"
#include "Game/Actors/Camera.hpp"
#include "Core/PotatoEngine.hpp"
#include "GameInstance.hpp"
#include "Core/Input/InputController.hpp"
#include "Util/GameplayHelper.hpp"
#include "Debug/Debug.hpp"

#include "PlayerController.hpp"

SET_DEFAULT_SUBCLASS(PlayerController, PlayerController);

PlayerController::PlayerController() {


}

void PlayerController::AssignPlayer(Player* player) {
    ActivePlayer = player;
    if (ActivePlayer == nullptr) {
        LOG_DEFAULT(LogType::WARNING, "Player set to nullptr during controller assignment");
    }
}

PlayerController::~PlayerController() {
    PotatoEngine::Get().GetInputController()->UnregisterAllInputBindings(this);
}

Player* PlayerController::GetPlayer() const { return ActivePlayer; }
Camera* PlayerController::GetCamera() const { return ActiveCamera; }

void PlayerController::MoveLeft() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(GameplayHelper::WorldToScreenDir(Vector2(-1.f, 0.f))); // Move left by 1 unit
}

void PlayerController::MoveRight() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(GameplayHelper::WorldToScreenDir(Vector2(1.f, 0.f))); // Move right by 1 unit
}

void PlayerController::MoveUp() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(GameplayHelper::WorldToScreenDir(Vector2(0.f, 1.f))); // Move left by 1 unit
}

void PlayerController::MoveDown() {
    if (ActivePlayer == nullptr) { return; }
    ActivePlayer->AddLocalOffset(GameplayHelper::WorldToScreenDir(Vector2(0.f, -1.f))); // Move left by 1 unit
}

void PlayerController::SetupInputBindings() {

    // setup input bindings
    IInputController* controller = PotatoEngine::Get().GetInputController();

    controller->RegisterInputBinding( InputBinding(Keycode::A, "MoveLeft", this, &PlayerController::MoveLeft) );
    controller->RegisterInputBinding( InputBinding(Keycode::D, "MoveRight", this, &PlayerController::MoveRight) );
    controller->RegisterInputBinding( InputBinding(Keycode::W, "MoveUp", this, &PlayerController::MoveUp) );
    controller->RegisterInputBinding( InputBinding(Keycode::S, "MoveDown", this, &PlayerController::MoveDown) );
}
