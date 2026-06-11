/** @file PhysicsController.hpp */
#pragma once

#include "Core/Singleton.hpp"
#include "Core/EngineSubsystem.hpp"
#include "Core/Event/Tickable.hpp"

#include "Util/Vector2.hpp"

class Actor;

class PhysicsController : public Singleton<PhysicsController>, public IEngineSubsystem, public Tickable
{
    friend class Singleton<PhysicsController>;

public:
    virtual void BeginPlay() override;
    virtual void Resolve() noexcept override;

protected:
    virtual void TickPostPhysics(float dt) override;

private:
    void UpdateActorPropertiesTick(Actor* actor, float dt);
    void ResolveCollision(Actor* a, Actor* b, const Vector2& aPos, const Vector2& bPos);

};