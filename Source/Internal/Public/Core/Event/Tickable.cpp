
#include "Core/PotatoEngine.hpp"
#include "Core/Event/TickController.hpp"

#include "Tickable.hpp"

bool Tickable::isTicking() const {
    return bTicking;
}

void Tickable::SetTicking(bool isEnabled) {
    /** DO NOT CALL IN CONSTRUCTOR */

    bTicking = isEnabled;

    ITickController* tickController = PotatoEngine::Get().GetTickController();

    if (isEnabled) {
        tickController->RegisterTick(EventDelegate<float>(this, &Tickable::Tick));
    } else {
        tickController->UnregisterTick(this);
    }
}

void Tickable::Tick(float dt) {}
Tickable::~Tickable() {}