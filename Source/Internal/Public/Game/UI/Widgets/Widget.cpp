
#include "Debug/Debug.hpp"
#include "Widget.hpp"

Widget::Widget(std::string UID) : UID(UID) {
    ScreenPosition = Vector2(0,0);
    Size = Vector2(16,4);
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
Vector2 Widget::GetScreenSize() const {
    return Size;
}
void Widget::SetScreenSize(const Vector2& size) {
    Size = size;
}
Vector2 Widget::GetScreenPosition() const { 
    return ScreenPosition; 
}
void Widget::SetScreenPosition(const Vector2 &ScreenPos) { 
    ScreenPosition = ScreenPos;
}
void Widget::AddScreenOffset(const Vector2& ScreenOffset) {
    SetScreenPosition(ScreenPosition + ScreenOffset);
}

bool Widget::isVisible() const {
    return Visible;
}
void Widget::SetVisibility(bool visibility) {
    Visible = visibility;
}

Widget::~Widget() {

    for (auto it = Elements.begin(); it != Elements.end(); it++ ) {
        delete it->second;
        Elements.erase(it);
    }

}