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
    wallB->ctex = 'W';

    Block* wallL = SpawnActor<Block>(Vector2(-wallWidth, 23));
    wallL->SetSize(Vector2(wallWidth, 24));
    wallL->ctex = 'W';

    Block* wallR = SpawnActor<Block>(Vector2(Settings.Size.x, 23));
    wallR->SetSize(Vector2(wallWidth, 24));
    wallR->ctex = 'W';

    Block* wallU = SpawnActor<Block>(Vector2(0, 23+wallWidth));
    wallU->SetSize(Vector2(Settings.Size.x, wallWidth));
    wallU->ctex = 'W';
    
    for (Actor* actor : actorPool) {
        actor->DispatchBeginPlay();
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
