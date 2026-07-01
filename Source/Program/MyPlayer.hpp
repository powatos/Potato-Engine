#pragma once

#include "Game/Actors/Player.hpp"
#include "Game/World/Raycast.hpp"

class MyPlayer : public Player
{

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float dt) override;
private:
    Raycast downraycast;
};