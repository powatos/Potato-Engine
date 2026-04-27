
#include "Core/EventController.hpp"
#include "Core/PotatoEngine.hpp"
#include "Debug/Debug.hpp"
#include "Util/GameplayHelper.hpp"

#include "Player.hpp"

Player::Player() {
    LOG_DEFAULT(LogType::DEBUG, "player1 instantiated");

    // setup input bindings
    IEventController* controller = PotatoEngine::Get().GetInputController();

    controller->RegisterInputBinding( InputBinding('a', "MoveLeft", this, &Player::MoveLeft) );
    controller->RegisterInputBinding( InputBinding('d', "MoveRight", this, &Player::MoveRight) );
    controller->RegisterInputBinding( InputBinding('w', "MoveUp", this, &Player::MoveUp) );
    controller->RegisterInputBinding( InputBinding('s', "MoveDown", this, &Player::MoveDown) );

}

Player::~Player() {
    LOG_DEFAULT(LogType::DEBUG, "player1 destroying");

    IEventController* controller = PotatoEngine::Get().GetInputController();

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