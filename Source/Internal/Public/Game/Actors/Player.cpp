/** @file Player.cpp */

#include "Core/Input/InputController.hpp"
#include "Core/PotatoEngine.hpp"
#include "Debug/Debug.hpp"
#include "Util/GameplayHelper.hpp"
#include "Game/Control/GameInstance.hpp"

#include "Player.hpp"

SET_DEFAULT_SUBCLASS(Player, Player)

Player::Player() {
    Texture = 'P';
    SetSize(Vector2(2,2));
    SetBounce(0.6f);
    SetUseAsymmetricGravity(true);
}

void Player::BeginPlay() {
    Actor::BeginPlay();

    SetSimulatingPhysics(true);
    SetTicking(true);
}

void Player::Tick([[maybe_unused]] float dt) {
    Entity::Tick(dt);

    // Texture = ((Texture - '0') + 1) % 10 + '0';

}

Player::~Player() {
}

