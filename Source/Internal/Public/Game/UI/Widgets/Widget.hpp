#pragma once

#include "Core/Event/Tickable.hpp"
#include "Util/Vector2.hpp"

class Widget : public Tickable
{
public:
    Widget(std::string UID);
    virtual ~Widget();

    const std::string& GetUID() const; 

    Vector2 GetScreenPosition() const;
    // make virtual to override for post-visibility change functionality (always call base method in first line)
    void SetScreenPosition(const Vector2& ScreenPosition);
    
    void AddScreenOffset(const Vector2& offset);
    
    bool isVisible() const;
    // make virtual to override for post-visibility change functionality (always call base method in first line)
    void SetVisibility(bool visibility); 

protected:
    Vector2 Size;


private:
    const std::string UID;

    bool Visible;
    Vector2 ScreenPosition;

};
