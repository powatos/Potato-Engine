#pragma once

#include "Core/Datastore/Archivable.hpp"
#include "Util/Vector2.hpp"

class Actor : public Archivable
{
public:
    
    Actor();
    Actor(Vector2 position);
    virtual ~Actor();

    Vector2 GetPosition() const;
    void SetPosition(const Vector2& position);
    
    float GetRotation() const;
    void SetRotation(float rotation);

    void AddLocalOffset(const Vector2& offset);
    void AddLocalRotation(float rotation);
    
private:

    void Destroy();
    
    Vector2 Position;
    float Rotation;
   
};