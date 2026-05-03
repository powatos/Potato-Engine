
// #include "Game/World.hpp"

#include "Widget.hpp"

Widget::Widget(std::string UID) : UID(UID) {
    ScreenPosition = Vector2(0,0);
    Visible = true;

}

const std::string& Widget::GetUID() const {
    return UID;
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

}