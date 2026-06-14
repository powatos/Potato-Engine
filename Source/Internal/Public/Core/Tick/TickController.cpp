/** @file TickController.cpp */

#include "TickController.hpp"

void TickController::Fire(float dt, TickGroup group) {

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
    tickables.push_back(tickable);
}