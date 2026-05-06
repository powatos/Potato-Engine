
#include "Game/Actors/Camera.hpp"
#include "Util/Vector2.hpp"

#include "GameplayHelper.hpp"

Vector2 GameplayHelper::VecToScreenVec(const Vector2& worldPos) {
    Vector2 vec = Vector2(worldPos.x, worldPos.y).Swizzled();
    vec.x = 23 - vec.x;
    return vec;
}

bool GameplayHelper::IsPositionInCameraFrame(const Vector2& pos, const Vector2& cameraPos) {
    
    return pos.x - cameraPos.x >= 0 && pos.x - cameraPos.x < 80;

}