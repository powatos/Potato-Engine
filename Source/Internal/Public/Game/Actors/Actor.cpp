/** @file Actor.cpp */

#include <algorithm>

#include "Util/Vector2.hpp"
#include "Debug/Debug.hpp"
#include "Game/World.hpp"
#include "Core/PotatoEngine.hpp"
#include "Core/Event/EventController.hpp"
#include "Game/Control/GameInstance.hpp"

#include "Actor.hpp"

ARCHIVE_STATIC(Actor);

Actor::Actor() {

    Position = Vector2();
    Size = Vector2();
    Rotation = 0.f;
    Visible = true;

    Mass = 10.f;
    SimulatePhysics = true;
    Movability = ActorMovability::Movable;
    
}

void Actor::DispatchBeginPlay() {
    if (isInPlay) { return; }
    isInPlay = true;

    BeginPlay();
}

void Actor::BeginPlay() {
    
}

void Actor::Tick(float dt) {
    Tickable::Tick(dt);


}

Vector2 Actor::GetPosition() const { 
    return Position; 
}
void Actor::SetPosition(const Vector2 &position) { 
    // TODO: enforce world bounds somewhere better later
    // World* world = GameInstance::get()->GetWorld();
    // Position = Vector2(
    //     std::clamp(position.x, 0.f, static_cast<float>(world->Settings.Size.x-1) - Size.x), 
    //     std::clamp(position.y, 0.f, static_cast<float>(world->Settings.Size.y-1)) // TODO: enforce position restriction for Y based on size
    // );
    Position = position;

}
void Actor::AddLocalOffset(const Vector2& offset) {
    SetPosition(Position + offset);
}

Vector2 Actor::GetVelocity() const { 
    return Velocity; 
}
void Actor::SetVelocity(const Vector2& velocity) { 
    Velocity = velocity;
}
void Actor::AddVelocity(const Vector2& velocity) {
    Velocity += velocity;
}

float Actor::GetMass() const {
    return Mass;
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

bool Actor::isSimulatingPhysics() const {
    return SimulatePhysics;
}
void Actor::SetSimulatingPhysics(bool enabled) {
    SimulatePhysics = enabled;
}

Vector2 Actor::GetForces() const {
    return Forces;
}
void Actor::AddForce(Vector2 force) {
    Forces += force;
}
void Actor::ClearForces() {
    Forces = Vector2(0.f, 0.f);
}

void Actor::AddImpulse(Vector2 force) {
    Velocity += force;
}

bool Actor::isVisible() const {
    return Visible;
}
void Actor::SetVisibility(bool visibility) {
    Visible = visibility;
}

float Actor::GetBounce() const {
    return Bounciness;
}
void Actor::SetBounce(float bounce) {
    Bounciness = bounce;
}

ActorMovability Actor::GetMovability() const {
    return Movability;
}
void Actor::SetMovability(ActorMovability movability) {
    Movability = movability;
}


Actor::~Actor() {

}
