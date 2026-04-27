#pragma once

struct Vector2;

class GameplayHelper {
    GameplayHelper() = default;

public:
    static Vector2 WorldToScreenPos(Vector2 worldPos);
    static Vector2 ScreenToWorldPos(Vector2 screenPos);

    static Vector2 WorldToScreenDir(Vector2 worldDir);
    static Vector2 ScreenToWorldDir(Vector2 screenDir);

};