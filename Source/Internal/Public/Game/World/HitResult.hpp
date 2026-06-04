/** @file HitResult.hpp */
#pragma once

#include "Util/Vector2.hpp"

class Actor;

/**
 * @brief Struct with information about a hit between two actors
 * @details This struct is used to pass information after physics collisions, raycasts, etc.
 */
struct HitResult
{
    Actor* otherActor;
    Vector2 hitPosition;
    Vector2 hitOverlap;
    Vector2 hitNormal;

    HitResult() = default;
    HitResult(Actor* otherActor, 
        Vector2 hitPosition, 
        Vector2 hitOverlap, 
        Vector2 hitNormal
    ) : 
        otherActor(otherActor), 
        hitPosition(hitPosition), 
        hitOverlap(hitOverlap), 
        hitNormal(hitNormal) 
    {}

};