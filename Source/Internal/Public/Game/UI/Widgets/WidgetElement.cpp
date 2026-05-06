
#include "WidgetElement.hpp"

Vector2 WidgetElement::GetPosition() const { 
    return Position; 
}
void WidgetElement::SetPosition(const Vector2 &position) { 
    // TODO: enforce world bounds somewhere better later
    Position = position;
}
void WidgetElement::AddOffset(const Vector2& offset) {
    SetPosition(Position + offset);
}
bool WidgetElement::isVisible() const {
    return Visible;
}
void WidgetElement::SetVisibility(bool visibility) {
    Visible = visibility;
}
