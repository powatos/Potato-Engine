
#include "Util/Vector2.hpp"

#include "GameplayHelper.hpp"

Vector2 GameplayHelper::WorldToScreenPos(Vector2 worldPos) {
    // TODO
    return worldPos;
}

Vector2 GameplayHelper::ScreenToWorldPos(Vector2 screenPos) {
    // TODO
    return Vector2();
}

Vector2 GameplayHelper::WorldToScreenDir(Vector2 worldDir) {
    return Vector2(-worldDir.Swizzled().x, worldDir.Swizzled().y);
}

Vector2 GameplayHelper::ScreenToWorldDir(Vector2 screenDir) {
    return Vector2();
}
