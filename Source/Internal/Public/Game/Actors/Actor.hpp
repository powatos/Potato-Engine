#pragma once

#include "Core/Datastore/Archivable.hpp"
#include "Core/Event/Tickable.hpp"
#include "Util/Vector2.hpp"

class Actor : public Archivable, public Tickable
{
public:
    
    Actor();
    virtual ~Actor();

    Vector2 GetPosition() const;
    void SetPosition(const Vector2& position);

    Vector2 GetSize() const;
    void SetSize(const Vector2& size);
    
    float GetRotation() const;
    void SetRotation(float rotation);

    void AddLocalOffset(const Vector2& offset);
    void AddLocalRotation(float rotation);
    
    bool isVisible() const;
    void SetVisibility(bool visibility);

    void DispatchBeginPlay();

    char Texture;
protected:

    virtual void BeginPlay();
    virtual void Tick(float dt) override;

private:

    bool Visible;

    Vector2 Position;
    Vector2 Size;
    float Rotation;

    bool isInPlay;
   
};