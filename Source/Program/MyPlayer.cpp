
#include "Core/Control/GameInstance.hpp"

#include "Debug/Debug.hpp"

#include "MyPlayer.hpp"

SET_DEFAULT_SUBCLASS(Player, MyPlayer)

MyPlayer::MyPlayer() : downraycast(Raycast()) {
    
}

void MyPlayer::BeginPlay() {
    downraycast.SetRay(Vector2(5,-5));
    downraycast.Settings.OverrideActorsList.insert(this);
    downraycast.Settings.OverrideActorsType = RaycastOverrideType::Exclude;
    downraycast.showDebug = true;
    downraycast.debugDuration = 1.0;
}

void MyPlayer::Tick(float dt) {
    HitResult hit;
    downraycast.origin = GetPosition() + Vector2::Right() * GetSize().x;
    downraycast.Cast(hit);

    // if (hit.hitActor) {
    //     LOG_DEFAULT(LogType::DEBUG, "{}", hit.distance); 
    // }
}