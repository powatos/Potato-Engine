/** @file Tickable.cpp */

#include "Core/PotatoEngine.hpp"
#include "Core/Event/EventController.hpp"

#include "Tickable.hpp"

bool Tickable::isTicking() const {
    return bTicking;
}

void Tickable::SetTicking(bool isEnabled) {
    /** DO NOT CALL IN CONSTRUCTOR */

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

void Tickable::Tick(float dt) {}
Tickable::~Tickable() {}