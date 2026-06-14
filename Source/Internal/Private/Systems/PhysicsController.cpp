/** @file PhysicsController.cpp */

#include "Game/Actors/Actor.hpp"
#include "Core/Control/GameInstance.hpp"
#include "Game/World/HitResult.hpp"

#include "Util/GameplayHelper.hpp"
#include "Debug/Debug.hpp"

#include "PhysicsController.hpp"

PhysicsController::PhysicsController() {
    LOG_DEFAULT(LogType::VITAL, "PhysicsController constructed");
    bTickingPostPhysics = true;
}

void PhysicsController::TickPostPhysics(float dt) {
    const ActorPool& actorPool = GameInstance::Get()->GetWorld()->GetAllActors();

    // update movement physics for each actor
    for (Actor* actor : actorPool) {
        if (!actor->isSimulatingPhysics()) { continue; }
        if (actor->GetMovability() == ActorMovability::Static) { continue; }

        UpdateActorPropertiesTick(actor, dt);
    }

    // update collision physics for each actor
    for (Actor* a : actorPool) {
        if (!a->isSimulatingPhysics()) { continue; }

        for (Actor* b : actorPool) {
            if (a >= b) { continue; } // pointer trick to avoid checking pairs twice and against self
            if (!b->isSimulatingPhysics()) { continue; }
            if (a->GetMovability() == ActorMovability::Static
                && b->GetMovability() == ActorMovability::Static ) { continue; }

            const Vector2 aPos = a->GetPosition();
            const Vector2 bPos = b->GetPosition();

            // broadphase check against actors farther than 100.f units
            if (aPos.SquaredDistance(bPos) >= 10'000.f) { continue; }

            ResolveCollision(a, b, aPos, bPos);
        }
    }

}

void PhysicsController::UpdateActorPropertiesTick(Actor* actor, float dt) {
    const World::WorldSettings& Settings = GameInstance::Get()->GetWorld()->Settings;
    
    // Sum all acting forces
    Vector2 forces = actor->GetForces();
    if (Settings.doGravity) {
        if (actor->IsUsingAsymmetricGravity() && actor->GetVelocity().Dot(Vector2::Up()) > 0.f) {
            forces += Vector2(0, -Settings.upGravity); 
        } else {
            // down gravity used if actor isnt asymettric
            forces += Vector2(0, -Settings.downGravity);
        }
    }

    const Vector2 acceleration = forces / actor->GetMass();
    const Vector2 dVelocity = acceleration * dt;

    actor->AddImpulse(dVelocity); // update velocity based on acceleration
    actor->AddLocalOffset(actor->GetVelocity() * dt); // update position

    actor->ClearForces(); // clear forces for next tick
}

void PhysicsController::ResolveCollision(Actor* a, Actor* b, const Vector2& aPos, const Vector2& bPos) {
    const World::WorldSettings& Settings = GameInstance::Get()->GetWorld()->Settings;

    const Vector2 aSize = a->GetSize();
    const Vector2 bSize = b->GetSize();
    const Vector2 aHalfSize = aSize * 0.5f;
    const Vector2 bHalfSize = bSize * 0.5f;
    const Vector2 aCenter = Vector2( aPos.x + aHalfSize.x , aPos.y - aHalfSize.y );
    const Vector2 bCenter = Vector2( bPos.x + bHalfSize.x , bPos.y - bHalfSize.y );
    const float dx = bCenter.x - aCenter.x;
    const float dy = bCenter.y - aCenter.y;
    const float overlapX = (aHalfSize.x + bHalfSize.x) - std::abs(dx);
    const float overlapY = (aHalfSize.y + bHalfSize.y) - std::abs(dy);

    // check for actual overlap
    if ( !(overlapX > 0.f && overlapY > 0.f) ) { return; }

    // calculate hit details
    HitResult hitResult;

    float penetration{};
    if (overlapX < overlapY) {
        penetration = overlapX;
        hitResult.hitNormal.x = dx > 0.f ? -1.f : 1.f;
    } else {
        penetration = overlapY;
        hitResult.hitNormal.y = dy > 0.f ? -1.f : 1.f;
    }
    
    // overlap box
    const float left = std::max(aPos.x, bPos.x);
    const float right = std::min(aPos.x + aSize.x, bPos.x + bSize.x);
    const float top = std::min(aPos.y, bPos.y);
    const float bot = std::max(aPos.y - aSize.y, bPos.y - bSize.y);

    hitResult.hitOverlap = Vector2(right - left, top - bot);
    hitResult.hitPosition = Vector2(left, top);

    // only apply collision correction if both actors are blocking
    if (a->GetCollisionType() == CollisionType::Block && b->GetCollisionType() == CollisionType::Block) {
        // calculate correction details
        const float seperationAmount = std::max(penetration - Settings.clipAllowed, 0.f) * Settings.clipDampeningFactor;
        const Vector2 correctionVector = hitResult.hitNormal * seperationAmount;

        // weighted correction based on mass
        const float aInvMass = a->GetMovability() == ActorMovability::Static ? 0.f : (1.f / a->GetMass());
        const float bInvMass = b->GetMovability() == ActorMovability::Static ? 0.f : (1.f / b->GetMass());
        const float totalInvMass = aInvMass + bInvMass;

        // correct positions
        if (totalInvMass > 0.f) {
            a->AddLocalOffset( correctionVector * (aInvMass / totalInvMass) );
            b->AddLocalOffset( -correctionVector * (bInvMass / totalInvMass) );
        }

        // apply impulse based on newtons law of restitution
        const Vector2 relativeVel = a->GetVelocity() - b->GetVelocity() ;
        const float normalVel = relativeVel.Dot(hitResult.hitNormal);

        if (normalVel < 0.f && totalInvMass > 0.f) {
            float restitution = a->GetBounce() * b->GetBounce(); // amount of bounce

            if (std::abs(normalVel) < Settings.bounceThreshold) { restitution = 0.f; } // low restitutions dont bounce

            const float impulseMag = -(1.f + restitution) * normalVel / totalInvMass;
            const Vector2 impulse = hitResult.hitNormal * impulseMag;

            // conservation of energy
            a->AddImpulse(impulse * aInvMass);
            b->AddImpulse(-impulse * bInvMass);
        }
    }   

    // always dispatch hit events even if not blocking
    HitResult HitResultA = hitResult;
    HitResultA.otherActor = b;
    a->OnHit(HitResultA);

    HitResult HitResultB = hitResult;
    HitResultB.otherActor = a;
    b->OnHit(HitResultB);
}

void PhysicsController::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving PhysicsController");
}

PhysicsController::~PhysicsController() {
    LOG_DEFAULT(LogType::VITAL, "PhysicsController destroying");
}