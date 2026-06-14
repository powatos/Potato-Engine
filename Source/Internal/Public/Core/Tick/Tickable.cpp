/** @file Tickable.cpp */

#include "Core/Event/EventController.hpp"
#include "TickController.hpp"
#include "Core/PotatoEngine.hpp"

#include "Tickable.hpp"

Tickable::Tickable() {
    TickController* controller = TickController::Get();

    controller->Register(this);
}

Tickable::~Tickable() {
    bTickingPreInput = false;
    bTickingUpdate = false;
    bTickingPostPhysics = false;
    bTickingPostRender = false;
}