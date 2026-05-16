#pragma once

#include "Game/Actors/Entity.hpp"

class PlayerController;

/**
 * @brief User controllable character
 */
class Player : public Entity
{

public:
    /**
     * @internal
     * @brief Constructs player
     */
    Player();
    virtual ~Player();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float dt) override;

private:
    // PlayerController* OwningController;

};
