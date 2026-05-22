/** @file HitResult.hpp */
#pragma once

#include "Util/Vector2.hpp"

class Actor;

/**
 * 
 */
struct HitResult
{
    Actor* otherActor;
    Vector2 hitPosition;
    Vector2 hitNormal;

    HitResult() : otherActor(nullptr), hitPosition(), hitNormal() {};
    HitResult(Actor* otherActor, Vector2 hitPosition, Vector2 hitNormal) : otherActor(nullptr), hitPosition(hitPosition), hitNormal(hitNormal) {}

};