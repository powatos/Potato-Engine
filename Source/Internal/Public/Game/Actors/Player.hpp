#pragma once

#include "Game/Actors/Entity.hpp"

class PlayerController;

class Player : public Entity
{

public:
    Player();
    virtual ~Player();

private:
    PlayerController* OwningController;

};
