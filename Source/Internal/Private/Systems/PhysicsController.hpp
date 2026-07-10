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

public:
    virtual void Resolve() noexcept override;

protected:
    PhysicsController();
    ~PhysicsController();

    virtual void _TickPhysics(float dt) override;

private:
    struct SweepResult
    {
        bool collided = false;
        float toi = 1.f;
        Vector2 normal;
        Vector2 overlap;
    };
    struct SweepPair
    {
        Actor* a;
        Actor* b;
        float toi;
        Vector2 normal;
        bool bothBlocking;
    };

    void UpdateActorVelocity(Actor* actor, float dt);
    
    SweepResult SweptAABB(
        const Vector2& aPos, const Vector2 bPos,
        const Vector2& aSize, const Vector2& bSize,
        const Vector2& relativeDisplacement
    ) const;

    void ApplyCollisionResponse(Actor* a, Actor* b, const Vector2& normal);
    void ResolveOverlapCollision(Actor* a, Actor* b, const Vector2& aPos, const Vector2& bPos);

};