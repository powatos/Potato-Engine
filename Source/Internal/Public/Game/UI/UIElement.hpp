#pragma once

#include "Util/Vector2.hpp"

class UIElement
{
public:
    Vector2 GetScreenSize() const;
    void SetScreenSize(const Vector2& size);

    Vector2 GetScreenPosition() const;
    void SetScreenPosition(const Vector2& ScreenPosition); // make virtual to override for post-visibility change functionality (always call base method in first line)
    
    void AddScreenOffset(const Vector2& offset);
    
    bool isVisible() const;
    void SetVisibility(bool visibility); // make virtual to override for post-visibility change functionality (always call base method in first line)

protected:
    Vector2 ScreenSize;
    Vector2 ScreenPosition;
    bool Visible;

};