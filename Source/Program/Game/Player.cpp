
// #include "Private/Systems/IOController.h"

#include "Player.h"

Player::Player() {

    // setup input bindings
    // IOController::get()->BindInput('a', &APlayer::MoveLeft);
    // IOController::get()->BindInput('d', &APlayer::MoveRight);

}

Player::~Player() {

}

void Player::MoveLeft() {
    AddLocalOffset(Vector2(-1.f, 0.f)); // Move left by 1 unit
}

void Player::MoveRight() {
    AddLocalOffset(Vector2(1.f, 0.f)); // Move right by 1 unit
}