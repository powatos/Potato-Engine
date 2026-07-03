/** @file Player.cpp */

#include "Core/Control/GameInstance.hpp"
#include "Core/Input/InputController.hpp"
#include "Core/PotatoEngine.hpp"

#include "Debug/Debug.hpp"
#include "Util/GameplayHelper.hpp"

#include "Player.hpp"

Player::Player() {
    SetSize(Vector2(2,2));
    SetBounce(0.6f);
    SetUseAsymmetricGravity(true);
    SetSimulatingPhysics(true);

    SetTexture("Player_default");
    ResizeToTexture();

}

void Player::BeginPlay() {
    Actor::BeginPlay();

}

void Player::Tick([[maybe_unused]] float dt) {
    Entity::Tick(dt);

}

Player::~Player() {
}

