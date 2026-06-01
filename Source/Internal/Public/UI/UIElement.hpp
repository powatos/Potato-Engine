/** @file UIElement.hpp */
#pragma once

#include "Util/Vector2.hpp"

/**
 * @brief Wrapper for elements that can be rendered on screen
 * @details Used for scaling size, position, offsets, and visibility parameters across different
 * types of UI targets
 */
class UIElement
{
public:
    virtual ~UIElement() = default;

    /** @brief Gets size of UI @returns Vector with x and y size components */
    Vector2 GetScreenSize() const;
    /** @brief Sets size of UI @param size Vector with x and y size components */
    void SetScreenSize(const Vector2& size);

    /** @brief Gets screen position of UI @returns Vector with x and y screen positions */
    Vector2 GetScreenPosition() const;
    /** @brief Sets screen position of UI @param ScreenPosition vector with x and y screen positions */
    void SetScreenPosition(const Vector2& ScreenPosition); // make virtual to override for post-visibility change functionality (always call base method in first line)
    
    /** @brief Adds offset to UI position @param offset Vector with offset direction */
    void AddScreenOffset(const Vector2& offset);
    
    /** @brief Checks if UI is visible @returns true if visible */
    bool isVisible() const;
    /** @brief Sets visibility of UI @param visibility Visibility to set */
    void SetVisibility(bool visibility); // make virtual to override for post-visibility change functionality (always call base method in first line)
    /** @brief Toggles visibility of UI */
    void ToggleVisibility();

private:
    Vector2 ScreenSize;
    Vector2 ScreenPosition;
    bool Visible;

};