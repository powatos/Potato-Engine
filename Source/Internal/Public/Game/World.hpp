#pragma once

#include <vector>
#include <type_traits>

#include "Util/Vector2.hpp"
#include "Game/Actors/Actor.hpp"

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
    template<typename ActorClass>
    ActorClass* SpawnActor(const Vector2& SpawnPosition);

    void DestroyActor(Actor* actor);
    // @returns actor if added; nullptr if not
    Actor* AddtoPool(Actor* actor);

    inline size_t ActorCount() const { return actorPool.size(); }
    const ActorPool& GetAllActors() const;

protected:

    ActorPool actorPool;

};

template<typename ActorClass>
ActorClass* World::SpawnActor() {
    static_assert(std::is_base_of_v<Actor, ActorClass>, "Illegal class spawn to world");

    ActorClass* actor = new ActorClass();
    actorPool.push_back(actor);

    return actor;
}

template<typename ActorClass>
ActorClass* World::SpawnActor(const Vector2& SpawnPosition) {
    Actor* actor = SpawnActor<ActorClass>();
    actor->SetPosition(SpawnPosition);

    return static_cast<ActorClass*>(actor);
}