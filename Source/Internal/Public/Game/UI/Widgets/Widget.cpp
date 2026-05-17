/** @file Widget.cpp */

#include "Debug/Debug.hpp"
#include "Widget.hpp"
#include "WidgetElement.hpp"

Widget::Widget(std::string UID) : UID(UID) {
    ScreenPosition = Vector2(0.0, 0.0);
    ScreenSize = Vector2(16.0, 4.0);
    Visible = true;

}

std::string Widget::GetUID() const {
    return UID;
}

const std::unordered_map<std::string, WidgetElement*>& Widget::GetAllElements() const {
    return Elements;
}
WidgetElement* Widget::GetElement(std::string name) {
    if (Elements.find(name) != Elements.end()) {
        return Elements.at(name);
    }

    return nullptr;
}

Widget::~Widget() {

    for (auto it = Elements.begin(); it != Elements.end(); ) {
        delete it->second;
        it = Elements.erase(it);
    }

}