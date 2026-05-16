#pragma once

#include <vector>
#include <type_traits>

#include "Util/Vector2.hpp"
#include "Game/Actors/Actor.hpp"

/** @brief Collection of actors in world */
using ActorPool = std::vector<Actor*>;

class Player;

/**
 * @brief Local level managing gameplay interactions
 */
class World
{
public:
    /** @brief x-width of game world */
    static constexpr int EXTENT_X = 1'000;
    /** @brief y-height of game world */
    static constexpr int EXTENT_Y = 24;
    
    /**
     * @internal
     * @brief Constructs world
     */
    World();
    ~World();

    /**
     * @brief Spawns Actor into world
     * * @tparam ActorClass Class of actor to spawn
     * @returns Actor added to world
     */
    template<typename ActorClass>
    ActorClass* SpawnActor();
    /**
     * @brief Spawns Actor into world
     * * @tparam ActorClass Class of actor to spawn
     * @param SpawnPosition Default world position for actor to be spawned at
     * @returns Actor added to world
     */
    template<typename ActorClass>
    ActorClass* SpawnActor(const Vector2& SpawnPosition);

    /**
     * @brief Destroys actor from world
     * @param actor Actor to destroy
     */
    void DestroyActor(Actor* actor);
    /**
     * @brief Attempts to add external actor object to world managing system
     * @warning Intended for internal use only. Always prefer spawning using regular logic.
     * @sa SpawnActor
     * @returns actor if successful
     */
    Actor* AddtoPool(Actor* actor);

    /** @brief Gets count of actors in world @returns Count */
    inline size_t ActorCount() const { return actorPool.size(); }
    /** @brief Gets ActorPool @returns actor pool */
    const ActorPool& GetAllActors() const;

protected: // TODO: make private
    Player* ActivePlayer;
    ActorPool actorPool;

};

template<typename ActorClass>
ActorClass* World::SpawnActor() {
    static_assert(std::is_base_of_v<Actor, ActorClass>, "Illegal class spawn to world");

    Actor* actor = new ActorClass();
    AddtoPool(actor);

    // post-spawn functionality here
    actor->DispatchBeginPlay();

    return static_cast<ActorClass*>(actor);
}

template<typename ActorClass>
ActorClass* World::SpawnActor(const Vector2& SpawnPosition) {
    Actor* actor = SpawnActor<ActorClass>();
    actor->SetPosition(SpawnPosition);

    return static_cast<ActorClass*>(actor);
}