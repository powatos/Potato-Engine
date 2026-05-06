
#include <algorithm>

#include "Util/Vector2.hpp"
#include "Debug/Debug.hpp"
#include "Game/World.hpp"

#include "Actor.hpp"

ARCHIVE_STATIC(Actor);

Actor::Actor() {

    Position = Vector2();
    Size = Vector2();
    Rotation = 0.f;
    Visible = true;
    
}

void Actor::DispatchBeginPlay() {
    if (isInPlay) { return; }
    isInPlay = true;

    BeginPlay();
}

void Actor::BeginPlay() {

}

void Actor::Tick(float dt) {

}

Vector2 Actor::GetPosition() const { 
    return Position; 
}
void Actor::SetPosition(const Vector2 &position) { 
    // TODO: enforce world bounds somewhere better later
    Position = Vector2(
        std::clamp(position.x, 0, World::EXTENT_X-1 - Size.x), 
        std::clamp(position.y, 0, World::EXTENT_Y-1) // TODO: enforce position restriction for Y based on size
    );
}
void Actor::AddLocalOffset(const Vector2& offset) {
    SetPosition(Position + offset);
}

Vector2 Actor::GetSize() const { 
    return Size; 
}
void Actor::SetSize(const Vector2 &size) { 
    // TODO: enforce size restrictions
    Size = size;
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
void Actor::AddLocalRotation(float rotation) {
    SetRotation(GetRotation() + rotation);
}

bool Actor::isVisible() const {
    return Visible;
}
void Actor::SetVisibility(bool visibility) {
    Visible = visibility;
}


Actor::~Actor() {

}
