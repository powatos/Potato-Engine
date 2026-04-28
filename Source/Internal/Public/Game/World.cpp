
#include "Debug/Debug.hpp"
#include "Game/Actors/Player.hpp"

#include "World.hpp"

World::World() {
    
}

World::~World() {

    while (!actorPool.empty()) {
        Actor* actor = actorPool.back();

        delete actor; // free memory
        actorPool.pop_back(); // erase nullptr
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