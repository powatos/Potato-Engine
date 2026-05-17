/** @file GameplayHelper.hpp */
#pragma once

class Camera;
struct Vector2;

/**
 * @brief Helper class with useful logic and shorthand functions
 * @details This class is uninstantiable. All helpers are `static`
 */
class GameplayHelper {
    GameplayHelper() = default;

public:
    /**
     * @brief Converts world position to screen position
     * @details World origin is game-relative (0,0). Screen origin is at the top left corner
     * of the terminal window. Use this function to convert world coordinates to screen-relative
     * @param worldPos position to convert
     * @returns converted screen position as vector
     */
    static Vector2 VecToScreenVec(const Vector2& worldPos);
    /**
     * @brief Checks if a position is visible in the view of a camera object
     * @param pos Position to check
     * @param cameraPos Position of camera
     * @returns true if is in frame
     */
    static bool IsPositionInCameraFrame(const Vector2& pos, const Vector2& cameraPos);
    // TODO: do camera relative
};