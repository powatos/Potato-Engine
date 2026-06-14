/** @file PhysicsController.hpp */
#pragma once

#include "Core/Singleton.hpp"
#include "Core/EngineSubsystem.hpp"
#include "Core/Tick/Tickable.hpp"

#include "Util/Vector2.hpp"

class Actor;

class PhysicsController : public EngineSubsystem<PhysicsController>, public Tickable
{
    ENGINE_SUBSYSTEM(PhysicsController)

protected:
    PhysicsController();

    virtual void TickPostPhysics(float dt) override;

private:
    void UpdateActorPropertiesTick(Actor* actor, float dt);
    void ResolveCollision(Actor* a, Actor* b, const Vector2& aPos, const Vector2& bPos);

};