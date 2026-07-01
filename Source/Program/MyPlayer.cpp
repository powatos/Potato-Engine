
#include "Core/Control/GameInstance.hpp"

#include "Debug/Debug.hpp"

#include "MyPlayer.hpp"

SET_DEFAULT_SUBCLASS(Player, MyPlayer)

void MyPlayer::BeginPlay() {
    downraycast = Raycast();
    downraycast.SetRay(Vector2(12,0));
    downraycast.Settings.OverrideActorsList.insert(this);
    downraycast.Settings.OverrideActorsType = RaycastOverrideType::Exclude;
}

void MyPlayer::Tick(float dt) {
    HitResult hit;
    downraycast.origin = GetPosition() + Vector2::Right() * GetSize().x;
    downraycast.Cast(hit);

    // if (hit.hitActor) {
    //     LOG_DEFAULT(LogType::DEBUG, "{}", hit.distance); 
    // }
}