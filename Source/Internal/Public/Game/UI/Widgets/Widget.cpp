
#include "Debug/Debug.hpp"
#include "Widget.hpp"
#include "WidgetElement.hpp"

Widget::Widget(std::string UID) : UID(UID) {
    ScreenPosition = Vector2(0,0);
    ScreenSize = Vector2(16,4);
    Visible = true;

}

std::string Widget::GetUID() const {
    return UID;
}

const std::unordered_map<std::string, WidgetElement*>& Widget::GetAllElements() const {
    return Elements;
}
WidgetElement* Widget::GetElement(std::string id) {
    if (Elements.find(id) != Elements.end()) {
        return Elements.at(id);
    }

    return nullptr;
}

Widget::~Widget() {

    for (auto it = Elements.begin(); it != Elements.end(); it++ ) {
        delete it->second;
        Elements.erase(it);
    }

}