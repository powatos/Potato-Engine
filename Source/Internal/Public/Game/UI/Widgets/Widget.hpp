#pragma once

#include <vector>

#include "Core/Event/Tickable.hpp"
#include "Game/UI/UIElement.hpp"

class WidgetElement;

class Widget : public Tickable, public UIElement
{
public:
    Widget(std::string UID);
    virtual ~Widget();

    std::string GetUID() const; 

    template<typename ElemType>
    ElemType* AddElement(std::string id);
    const std::unordered_map<std::string, WidgetElement*>& GetAllElements() const;
    WidgetElement* GetElement(std::string id);

protected:


    std::unordered_map<std::string, WidgetElement*> Elements;

private:
    const std::string UID;

};

template<typename ElemType>
ElemType* Widget::AddElement(std::string id) {
    ElemType* elem = new ElemType();
    Elements[id] = elem;

    return elem;
}