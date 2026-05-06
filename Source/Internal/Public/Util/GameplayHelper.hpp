#pragma once

class Camera;
struct Vector2;

class GameplayHelper {
    GameplayHelper() = default;

public:
    static Vector2 VecToScreenVec(const Vector2& worldPos);
    static bool IsPositionInCameraFrame(const Vector2& pos, const Vector2& cameraPos);

};