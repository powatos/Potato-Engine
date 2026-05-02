
#include "Game/Actors/Camera.hpp"
#include "Util/Vector2.hpp"

#include "GameplayHelper.hpp"

Vector2 GameplayHelper::WorldToScreenPos(Vector2 worldPos, const Camera* camera) {
    // TODO
    Vector2 vec = Vector2(worldPos.x, worldPos.y).Swizzled();
    vec.x = 23 - vec.x;
    return vec;
    
}

Vector2 GameplayHelper::ScreenToWorldPos(Vector2 screenPos, const Camera* camera) {
    // TODO
    return Vector2();
}

Vector2 GameplayHelper::WorldToScreenDir(Vector2 worldDir) {
    return Vector2(-worldDir.Swizzled().x, worldDir.Swizzled().y);
}

Vector2 GameplayHelper::ScreenToWorldDir(Vector2 screenDir) {
    return Vector2();
}
