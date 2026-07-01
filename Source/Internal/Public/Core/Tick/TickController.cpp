/** @file TickController.cpp */

#include "TickController.hpp"

TickController::TickController() {
    LOG_DEFAULT(LogType::VITAL, "TickController constructed");
}

void TickController::Fire(float dt, TickGroup group) {

    // add from queue
    tickables.reserve(tickables.size() + tickablesQueue.size());
    tickables.insert(
        tickables.end(),
        std::make_move_iterator(tickablesQueue.begin()),
        std::make_move_iterator(tickablesQueue.end())
    );
    tickablesQueue.clear();

    for (Tickable* obj : tickables) {
        checkObjByGroup(dt, group, obj);
    }
}

constexpr void TickController::checkObjByGroup(float dt, TickGroup group, Tickable* obj) {
    switch (group) {
        case TickGroup::PreInput:
            if (obj->bTickingPreInput) { obj->TickPreInput(dt); } 
            break;
        case TickGroup::Update:
            if (obj->bTickingUpdate) { obj->Tick(dt); }
            break;
        case TickGroup::PostPhysics:
            if (obj->bTickingPostPhysics) { obj->TickPostPhysics(dt); }
            break;
        case TickGroup::PostRender:
            if (obj->bTickingPostRender) { obj->TickPostRender(dt); }
            break;
    }
}

void TickController::Register(Tickable* tickable) {
    tickablesQueue.push_back(tickable);
}

void TickController::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving TickController");
}

TickController::~TickController() {
    LOG_DEFAULT(LogType::VITAL, "TickController destroying");
}