/** @file World.cpp */

#include "Debug/Debug.hpp"
#include "Game/Actors/Player.hpp"
#include "Util/GameplayHelper.hpp"
#include "Game/Actors/Block.hpp"

#include "fmt/core.h"

#include "World.hpp"

World::World() {

    Settings = WorldSettings();
    
}

void World::_BeginPlay() {
    const int wallWidth = 5;

    Block* wallB = SpawnActor<Block>(Vector2(0, -1));
    wallB->SetSize(Vector2(Settings.Size.x, wallWidth));
    wallB->Texture = 'W';

    Block* wallL = SpawnActor<Block>(Vector2(-wallWidth, 23));
    wallL->SetSize(Vector2(wallWidth, 24));
    wallL->Texture = 'W';

    Block* wallR = SpawnActor<Block>(Vector2(Settings.Size.x, 23));
    wallR->SetSize(Vector2(wallWidth, 24));
    wallR->Texture = 'W';

    Block* wallU = SpawnActor<Block>(Vector2(0, 23+wallWidth));
    wallU->SetSize(Vector2(Settings.Size.x, wallWidth));
    wallU->Texture = 'W';
}

void World::__TickPhysics(float dt) {


    for (Actor* actor : actorPool) {
        if (!actor->isSimulatingPhysics()) { continue; }
        if (actor->GetMovability() == ActorMovability::Static) { continue; }
        // todo: asymettric. then do debug format
        Vector2 forces = actor->GetForces();

        if (Settings.doGravity && actor->GetVelocity().Dot(Vector2::Up()) > 0.f) {
            forces += Vector2(0, -Settings.upGravity); 
        } else {
            // down gravity used if actor isnt asymettric
            forces += Vector2(0, -Settings.downGravity);
        }

        const Vector2 acceleration = forces / actor->GetMass();
        const Vector2 dVelocity = acceleration * dt;

        actor->AddVelocity(dVelocity);

        actor->AddLocalOffset(actor->GetVelocity() * dt);
        actor->ClearForces();
    }

    ResolveCollisions();
}

void World::ResolveCollisions() {

    for (Actor* a : actorPool) {
        if (!a->isSimulatingPhysics()) { continue; }
    for (Actor* b : actorPool) {
        if (a >= b) { continue; }
        if (!b->isSimulatingPhysics()) { continue; }

        const Vector2 aPos = a->GetPosition();
        const Vector2 bPos = b->GetPosition();

        // assumes max distance between actor origins (not calculating size) is < 100.f
        if (aPos.SquaredDistance(bPos) >= 10'000.f) { continue; }

        const Vector2 aHalfSize = a->GetSize() * 0.5f;
        const Vector2 bHalfSize = b->GetSize() * 0.5f;
        const Vector2 aCenter = Vector2( aPos.x + aHalfSize.x , aPos.y - aHalfSize.y );
        const Vector2 bCenter = Vector2( bPos.x + bHalfSize.x , bPos.y - bHalfSize.y );
        const float dx = bCenter.x - aCenter.x;
        const float dy = bCenter.y - aCenter.y;
        const float overlapX = (aHalfSize.x + bHalfSize.x) - std::abs(dx);
        const float overlapY = (aHalfSize.y + bHalfSize.y) - std::abs(dy);

        if ( !(overlapX > 0.f && overlapY > 0.f) ) { continue; }

        Vector2 normal{};
        float penetration{};
        if (overlapX < overlapY) {
            penetration = overlapX;
            normal.x = dx > 0.f ? -1.f : 1.f;
        } else {
            penetration = overlapY;
            normal.y = dy > 0.f ? -1.f : 1.f;
        }

        const float seperationAmount = std::max(penetration - Settings.clipAllowed, 0.f) * Settings.clipDampeningFactor;
        const Vector2 correctionVector = normal * seperationAmount;

        const float aInvMass = a->GetMovability() == ActorMovability::Static ? 0.f : (1.f / a->GetMass());
        const float bInvMass = b->GetMovability() == ActorMovability::Static ? 0.f : (1.f / b->GetMass());
        const float totalInvMass = aInvMass + bInvMass;

        if (totalInvMass > 0.f) {
            a->AddLocalOffset( correctionVector * (aInvMass / totalInvMass) );
            b->AddLocalOffset( -correctionVector * (bInvMass / totalInvMass) );
        }

        const Vector2 relativeVel = a->GetVelocity() - b->GetVelocity() ;
        const float normalVel = relativeVel.Dot(normal);
        if (normalVel < 0.f && totalInvMass > 0.f) {
            float restitution = a->GetBounce() * b->GetBounce();

            if (std::abs(normalVel) < Settings.bounceThreshold) { restitution = 0.f; }
            const float impulseMag = -(1.f + restitution) * normalVel / totalInvMass;
            const Vector2 impulse = normal * impulseMag;

            a->AddImpulse(impulse * aInvMass);
            b->AddImpulse(-impulse * bInvMass);
        }

        //a.FireOverlap();
        //b.FireOverlap();

    }
    }

}

void World::DestroyActor(Actor* actor) {
    auto it = std::find(actorPool.begin(), actorPool.end(), actor);
    
    if (it != actorPool.end()) {
        delete *it; // free memory
        actorPool.erase(it); // erase nullptr
    }
}

const ActorPool& World::GetAllActors() const
{
    return actorPool;
}

Actor* World::AddtoPool(Actor* actor) {
    if (actor == nullptr) { return nullptr; }

    actorPool.push_back(actor);
    return actor;
}

World::~World() {

    while (!actorPool.empty()) {
        Actor* actor = actorPool.back();

        delete actor; // free memory
        actorPool.pop_back(); // erase nullptr
    }

}
