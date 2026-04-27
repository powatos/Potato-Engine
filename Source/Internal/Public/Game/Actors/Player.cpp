
#include "Core/EventController.hpp"
#include "Core/PotatoEngine.hpp"
#include "Debug/Debug.hpp"

#include "Player.hpp"

Player::Player() {
    LOG_DEFAULT(LogType::DEBUG, "player1 instantiated");

    // setup input bindings
    IEventController* controller = PotatoEngine::Get().GetInputController();

    controller->RegisterInputBinding( InputBinding('a', "MoveLeft", this, &Player::MoveLeft) );
    controller->RegisterInputBinding( InputBinding('d', "MoveRight", this, &Player::MoveRight) );

}

Player::~Player() {
    LOG_DEFAULT(LogType::DEBUG, "player1 destroying");

    IEventController* controller = PotatoEngine::Get().GetInputController();

    controller->UnregisterAllInputBindings(this);
}

void Player::MoveLeft() {
    AddLocalOffset(Vector2(-1.f, 0.f)); // Move left by 1 unit
}

void Player::MoveRight() {
    AddLocalOffset(Vector2(1.f, 0.f)); // Move right by 1 unit
}