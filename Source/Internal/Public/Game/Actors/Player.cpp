
#include "Core/Input/InputController.hpp"
#include "Core/PotatoEngine.hpp"
#include "Debug/Debug.hpp"
#include "Util/GameplayHelper.hpp"
#include "Game/Control/GameInstance.hpp"

#include "Player.hpp"

SET_DEFAULT_SUBCLASS(Player, Player);

Player::Player() {
}

void Player::BeginPlay() {
    SetTicking(true);
}

void Player::Tick(float dt) {

    Texture = ((Texture - '0') + 1) % 10 + '0';

}

Player::~Player() {
}

