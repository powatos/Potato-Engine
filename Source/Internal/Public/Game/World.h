#pragma once

#include <vector>

#include "Game/Actor.h"

using ActorPool = std::vector<Actor*>;

class World
{
public:
    static constexpr int EXTENT_X = 1'000;
    static constexpr int EXTENT_Y = 40;
  
    World();
    ~World();

    template<typename ActorClass>
    ActorClass* SpawnActor();
    void DespawnActor(Actor* actor);
    // @returns actor if added; nullptr if not
    Actor* AddtoPool(Actor* actor);

    inline size_t ActorCount() const { return actorPool.size(); }
    const ActorPool& GetAllActors() const;

protected:

    ActorPool actorPool;

};

template<typename ActorClass>
ActorClass* World::SpawnActor() {
    ActorClass* actor = new ActorClass();
    actorPool.push_back(actor);

    return actor;
}