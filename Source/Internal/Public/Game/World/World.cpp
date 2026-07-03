/** @file World.cpp */

#include "Game/Actors/Block.hpp"
#include "Game/Actors/Player.hpp"

#include "Debug/Debug.hpp"

#include "World.hpp"

World::World() {

    Settings = WorldSettings();
    
}

void World::BeginPlay() {
    const int wallWidth = 5;

    Block* wallB = SpawnActor<Block>(Vector2(0, -1));
    wallB->SetSize(Vector2(Settings.Size.x, wallWidth));
    wallB->ctex = 'B';

    Block* wallL = SpawnActor<Block>(Vector2(-wallWidth, 23));
    wallL->SetSize(Vector2(wallWidth, 24));
    wallL->ctex = 'L';

    Block* wallR = SpawnActor<Block>(Vector2(Settings.Size.x, 23));
    wallR->SetSize(Vector2(wallWidth, 24));
    wallR->ctex = 'R';

    Block* wallU = SpawnActor<Block>(Vector2(0, 24+wallWidth));
    wallU->SetSize(Vector2(Settings.Size.x, wallWidth));
    wallU->ctex = 'U';
    
    for (Actor* actor : actorPool) {
        actor->DispatchBeginPlay();
    }
}

void World::DestroyActor(Actor* actor) {
    destroyQueue.push_back(actor);
}

void World::TickPostUpdate(float dt) {

    for (auto it0 = destroyQueue.begin(); it0 != destroyQueue.end();) {
        auto it1 = std::find(actorPool.begin(), actorPool.end(), *it0);
    
        if (it1 != actorPool.end()) {
            delete *it1; // free memory
            actorPool.erase(it1); // erase nullptr
        }

        it0 = destroyQueue.erase(it0);

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
