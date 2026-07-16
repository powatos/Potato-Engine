/** @file PhysicsController.cpp */

#include <limits>
#include <unordered_map>

#include "Game/Actors/Actor.hpp"
#include "Core/Control/GameInstance.hpp"
#include "Game/World/HitResult.hpp"

#include "Util/GameplayHelper.hpp"
#include "Debug/Debug.hpp"

#include "PhysicsController.hpp"

PhysicsController::PhysicsController() {
    LOG_DEFAULT(LogType::VITAL, "PhysicsController constructed");
}

void PhysicsController::_TickPhysics(float dt) {
    const World* world = GameInstance::Get()->GetWorld();
    const World::WorldSettings Settings = world->Settings;
    const ActorPool& actorPool = world->GetAllActors();

    // update velocity for each actor
    for (Actor* actor : actorPool) {
        if (!actor->isSimulatingPhysics()) { continue; }
        if (actor->GetMovability() == ActorMovability::Static) { continue; }
        
        Vector2 forces = actor->GetForces();
        if (Settings.doGravity) {
            if (actor->IsUsingAsymmetricGravity() && actor->GetVelocity().Dot(Vector2::Up()) > 0.f) {
                forces += Vector2(0, -Settings.upGravity);
            } else {
                forces += Vector2(0, -Settings.downGravity);
            }
        }

        const Vector2 acceleration = forces / actor->GetMass();
        const Vector2 dVelocity = acceleration * dt;

        actor->AddImpulse(dVelocity);
        actor->ClearForces();
    }

    for (Actor* a : actorPool) {
        if (a->GetCollisionType() == CollisionType::None) { continue; }

        for (Actor* b : actorPool) {
            if (a >= b) { continue; } // pointer trick to avoid checking pairs twice and against self
            if (b->GetCollisionType() == CollisionType::None) { continue; }

            using CV = const Vector2;

            CV aPos = a->GetPosition();
            CV bPos = b->GetPosition();
            CV aSize = a->GetSize();
            CV bSize = b->GetSize();

            using CF = const float;
            
            // broadphase check against actors farther than 10'000.f units
            CF broadphaseRadius = 10'000.f;
            if (aPos.SquaredDistance(bPos) >= broadphaseRadius * broadphaseRadius) { continue; }

            CF nbxmin = bPos.x - aSize.x;
            CF nbxmax = bPos.x + bSize.x;
            CF nbymin = bPos.y - bSize.y;
            CF nbymax = bPos.y + aSize.y;
            CV ep = aPos + a->GetVelocity() * dt;

            CF xraydist = ep.x - aPos.x;
            CF yraydist = ep.y - aPos.y;   

            using F = float;

            // TODO: optimize division using INV checks
            F xtentry = xraydist != 0.f ? (nbxmin - aPos.x) / xraydist : std::numeric_limits<float>::infinity();
            F xtexit = xraydist != 0.f ? (nbxmax - aPos.x) / xraydist : std::numeric_limits<float>::infinity();
            F ytentry = yraydist != 0.f ? (nbymin - aPos.y) / yraydist : std::numeric_limits<float>::infinity();
            F ytexit = yraydist != 0.f ? (nbymax - aPos.y) / yraydist : std::numeric_limits<float>::infinity();

            if (xtentry > xtexit) { std::swap(xtentry, xtexit); }
            if (ytentry > ytexit) { std::swap(ytentry, ytexit); }

            if (xtentry > 0.f && ytentry > 0.f) {
                // a started inside
            } else if (xtentry > 1.f && ytentry > 1.f) {
                // a ends inside
            }
            
            


        }
    }

}

void PhysicsController::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving PhysicsController");
}

PhysicsController::~PhysicsController() {
    LOG_DEFAULT(LogType::VITAL, "PhysicsController destroying");
}