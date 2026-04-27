#pragma once

#include "Actor.hpp"

class Entity : public Actor 
{
public:
    Entity();
    virtual ~Entity();

    // @returns new health
    float TakeDamage(float damage);

    // @returns new health
    float AddHealth(float amount);
    float GetHealth() const;

protected:
    float Health;
    float MaxHealth;

};