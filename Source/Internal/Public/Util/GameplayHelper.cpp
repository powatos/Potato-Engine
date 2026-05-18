/** @file GameplayHelper.cpp */

#include "Game/Actors/Camera.hpp"
#include "Util/Vector2.hpp"

#include "GameplayHelper.hpp"

Vector2 GameplayHelper::VecToScreenVec(const Vector2& worldPos) {
    Vector2 vec = Vector2(worldPos.x, worldPos.y).Swizzled();
    vec.x = 23.f - vec.x;
    return vec;
}

bool GameplayHelper::IsPositionInCameraFrame(const Vector2& pos, Camera* camera) {
    
    return pos.x - camera->GetPosition().x >= 0.f && pos.x - camera->GetPosition().x < camera->GetSize().x;



}