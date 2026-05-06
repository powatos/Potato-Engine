#pragma once

#include "Game/Actors/Entity.hpp"

class PlayerController;

class Player : public Entity
{

public:
    Player();
    virtual ~Player();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float dt) override;

private:
    // PlayerController* OwningController;

};
