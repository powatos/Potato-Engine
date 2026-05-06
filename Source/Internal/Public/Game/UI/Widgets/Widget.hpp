#pragma once

#include <vector>

#include "Core/Event/Tickable.hpp"
#include "Util/Vector2.hpp"
#include "WidgetElement.hpp"

class Widget : public Tickable
{
public:
    Widget(std::string UID);
    virtual ~Widget();

    std::string GetUID() const; 

    template<typename ElemType>
    ElemType* AddElement(std::string id);
    const std::unordered_map<std::string, WidgetElement*>& GetAllElements() const;
    WidgetElement* GetElement(std::string id);

    Vector2 GetScreenSize() const;
    void SetScreenSize(const Vector2& size);

    Vector2 GetScreenPosition() const;
    void SetScreenPosition(const Vector2& ScreenPosition); // make virtual to override for post-visibility change functionality (always call base method in first line)
    
    void AddScreenOffset(const Vector2& offset);
    
    bool isVisible() const;
    void SetVisibility(bool visibility); // make virtual to override for post-visibility change functionality (always call base method in first line)


protected:
    Vector2 Size;
    Vector2 ScreenPosition;

    std::unordered_map<std::string, WidgetElement*> Elements;

private:
    const std::string UID;

    bool Visible;

};

template<typename ElemType>
ElemType* Widget::AddElement(std::string id) {
    ElemType* elem = new ElemType();
    Elements[id] = elem;

    return elem;
}