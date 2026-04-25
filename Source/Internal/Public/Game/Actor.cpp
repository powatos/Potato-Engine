
#include "Util/Vector2.h"
#include "Debug/Debug.h"

#include "Actor.h"

int Actor::_ = []() {
        __Archive::_GetArchive()["Actor"] = []() -> Archivable* { return new Actor(); };
        LOG_DEFAULT(LogType::INFO, "actor inst callback archived");
        return 0;
    }();

Actor::Actor() {

    Position = Vector2();
    Rotation = 0.f;
    
}

Actor::Actor(Vector2 position) {

    Position = position;
    Rotation = 0.f;
    
}

Vector2 Actor::GetPosition() const { 
    return Position; 
}
void Actor::SetPosition(const Vector2 &position) { 
    Position = position; 
}
float Actor::GetRotation() const { 
    return Rotation; 
}
void Actor::SetRotation(float rotation) {

    // Normalize rotation to [0, 360)
    rotation = fmodf(rotation, 360.0f);
    if (rotation < 0.0f) { rotation += 360.0f; }
    Rotation = rotation;
}
void Actor::AddLocalOffset(const Vector2& offset) {
    SetPosition(Position + offset);
}
void Actor::AddLocalRotation(float rotation) {
    SetRotation(GetRotation() + rotation);
}

void Actor::Destroy() {
    
}
