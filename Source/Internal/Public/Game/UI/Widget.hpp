#pragma once

#include "Core/Event/Tickable.hpp"
#include "Util/Vector2.hpp"

class Widget : public Tickable
{
public:
    Widget();
    virtual ~Widget();

    Vector2 GetScreenPosition() const;
    void SetScreenPosition(const Vector2& ScreenPosition);
    
    void AddScreenOffset(const Vector2& offset);
    
    bool isVisible() const;
    void SetVisibility(bool visibility);

protected:

private:
    
    bool Visible;
    Vector2 ScreenPosition;

};