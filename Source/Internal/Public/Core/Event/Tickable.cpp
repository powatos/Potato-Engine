/** @file Tickable.cpp */

#include "Core/PotatoEngine.hpp"
#include "Core/Event/EventController.hpp"

#include "Tickable.hpp"

bool Tickable::isTicking() const {
    return bTicking;
}

void Tickable::SetTicking(bool isEnabled) {

    bTicking = isEnabled;

    EventController* controller = PotatoEngine::Get().GetNativeEventController();

    if (isEnabled) {
        controller->RegisterNativeEvent(
            "__ENGINE_TICK",
            NativeEventBinding<float>("__engine_tick_binding", this, &Tickable::Tick)
        );
        
    } else {
        controller->UnregisterNativeEvent<float>("__ENGINE_TICK", this);
    }
}

bool Tickable::isTickingPostPhysics() const {
    return bTickingPostPhysics;
}

void Tickable::SetTickingPostPhysics(bool isEnabled) {
    bTickingPostPhysics = isEnabled;

    EventController* controller = PotatoEngine::Get().GetNativeEventController();

    if (isEnabled) {
        controller->RegisterNativeEvent(
            "__ENGINE_TICK_POST_PHYSICS",
            NativeEventBinding<float>("__engine_tick_post_physics_binding", this, &Tickable::TickPostPhysics)
        );
        
    } else {
        controller->UnregisterNativeEvent<float>("__ENGINE_TICK_POST_PHYSICS", this);
    }
}

void Tickable::Tick([[maybe_unused]] float dt) {

}
Tickable::~Tickable() {
    SetTicking(false); 
    SetTickingPostPhysics(false);   
}