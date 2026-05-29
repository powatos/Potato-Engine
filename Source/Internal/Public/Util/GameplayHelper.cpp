/** @file GameplayHelper.cpp */

#include "Game/Actors/Camera.hpp"
#include "Util/Vector2.hpp"
#include "Core/Control/GameInstance.hpp"
#include "Game/World.hpp"
#include "Game/Actors/Actor.hpp"

#include "GameplayHelper.hpp"

Vector2 GameplayHelper::VecToScreenVec(const Vector2& worldPos) {
    Vector2 vec = Vector2(worldPos.x, worldPos.y).Swizzled();
    vec.x = 23.f - vec.x;
    return vec;
}

bool GameplayHelper::IsPositionInCameraFrame(const Vector2& pos, Camera* camera) {
    
    return pos.x - camera->GetPosition().x >= 0.f && pos.x - camera->GetPosition().x < camera->GetSize().x;

}

std::vector<Actor*> GameplayHelper::GetOverlappingActors(const Actor* actor) {
    std::vector<Actor*> result{};

    for (Actor* otherActor : GameInstance::get()->GetWorld()->GetAllActors()) {
        if (actor != otherActor && IsActorOverlapping(actor, otherActor)) {
            result.push_back(otherActor);
        }
    }

    return result;
}

bool GameplayHelper::IsActorOverlapping(const Actor* actor1, const Actor* actor2) {
    if (actor1 == actor2) { return true; }

    const Vector2 a1Pos = actor1->GetPosition();
    const Vector2 a1Siz = actor1->GetSize();
    const Vector2 a2Pos = actor2->GetPosition();
    const Vector2 a2Siz = actor2->GetSize();

    return 
        a1Pos.x < a2Pos.x + a2Siz.x && // left side check
        a1Pos.x + a1Siz.x > a2Pos.x && // right side check
        a1Pos.y < a2Pos.y + a2Siz.y && // top side check
        a1Pos.y + a1Siz.y > a2Pos.y // bottom side check
    ;
}