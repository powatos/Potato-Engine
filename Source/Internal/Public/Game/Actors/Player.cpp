
#include "Core/Input/InputController.hpp"
#include "Core/PotatoEngine.hpp"
#include "Debug/Debug.hpp"
#include "Util/GameplayHelper.hpp"

#include "Player.hpp"

Player::Player() {

    // setup input bindings
    IInputController* controller = PotatoEngine::Get().GetInputController();

    controller->RegisterInputBinding( InputBinding(Keycode::A, "MoveLeft", this, &Player::MoveLeft) );
    controller->RegisterInputBinding( InputBinding(Keycode::D, "MoveRight", this, &Player::MoveRight) );
    controller->RegisterInputBinding( InputBinding(Keycode::W, "MoveUp", this, &Player::MoveUp) );
    controller->RegisterInputBinding( InputBinding(Keycode::S, "MoveDown", this, &Player::MoveDown) );

}

Player::~Player() {

    IInputController* controller = PotatoEngine::Get().GetInputController();

    controller->UnregisterAllInputBindings(this);
}

void Player::MoveLeft() {
    AddLocalOffset(GameplayHelper::WorldToScreenDir(Vector2(-1.f, 0.f))); // Move left by 1 unit
}

void Player::MoveRight() {
    AddLocalOffset(GameplayHelper::WorldToScreenDir(Vector2(1.f, 0.f))); // Move right by 1 unit
}

void Player::MoveUp() {
    AddLocalOffset(GameplayHelper::WorldToScreenDir(Vector2(0.f, 1.f))); // Move left by 1 unit
}

void Player::MoveDown() {
    AddLocalOffset(GameplayHelper::WorldToScreenDir(Vector2(0.f, -1.f))); // Move left by 1 unit
}