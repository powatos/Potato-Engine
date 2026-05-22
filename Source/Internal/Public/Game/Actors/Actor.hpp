/** @file Actor.hpp */
#pragma once

#include "Core/Datastore/Archivable.hpp"
#include "Core/Event/Tickable.hpp"
#include "Util/Vector2.hpp"

enum class ActorMovability
{
    Movable,
    Static
};

/**
 * @brief Base actor class
 * @details This class represents a level object that exists in the game world. All objects that obey world
 * physics must inherit from Actor base
 */
class Actor : public Archivable, public Tickable
{
public:
    
    /**
     * @brief Constructs actor object
     * @details Put all class level functionality here (member initializations, 
     * default values, etc.)
     * @warning Never construct actors manually. @sa World::SpawnActor
     */
    Actor();
    virtual ~Actor();

    /** @brief Gets position @returns Position */
    Vector2 GetPosition() const;
    /** @brief Sets position @param position Position to set */
    void SetPosition(const Vector2& position);

    Vector2 GetVelocity() const;
    void SetVelocity(const Vector2& velocity);
    void AddVelocity(const Vector2& velocity);

    /** @brief Gets size @returns Size */
    Vector2 GetSize() const;
    /** @brief Sets size @param size Size to set */
    void SetSize(const Vector2& size);
    
    /** @brief Gets rotation @returns rotation */
    float GetRotation() const;
    /** @brief Sets rotation @param rotation Rotation to set (degrees) */
    void SetRotation(float rotation);

    /** @brief Adds to location vector @param offset Offset to add */
    void AddLocalOffset(const Vector2& offset);
    /** @brief Adds to rotation value @param rotation Rotation to add */
    void AddLocalRotation(float rotation);

    bool isSimulatingPhysics() const;
    void SetSimulatingPhysics(bool enabled);

    Vector2 GetForces() const;
    void AddForce(Vector2 force);
    void ClearForces();

    void AddImpulse(Vector2 force);

    float GetMass() const;

    bool IsUsingAsymmetricGravity() const;
    void SetUseAsymmetricGravity(bool useAsymmetricGravity);

    ActorMovability GetMovability() const;
    void SetMovability(ActorMovability movability);

    float GetBounce() const;
    void SetBounce(float bounce);
    
    /** @brief Checks if actor visible @returns true if visible */
    bool isVisible() const;
    /** @brief Sets visibility of actor @param visibility Visibility to set */
    void SetVisibility(bool visibility);

    /**
     * @brief Internal function used to queue BeginPlay() on actor
     */
    void DispatchBeginPlay();

    char Texture;
protected:

    /**
     * @brief Gameplay start
     * @details Put all pre-gameplay functionality here
     * @note Always call base method when overriding:
     * @code
     * void ActorClass::BeginPlay() {
     *     BaseActor::BeginPlay();
     *     // ...
     * }
     * @endcode
     */
    virtual void BeginPlay();
    
    virtual void Tick(float dt) override;

private:

    Vector2 Position;
    Vector2 Velocity;
    Vector2 Forces;
    Vector2 Size;
    
    ActorMovability Movability;

    float Bounciness;
    float Mass;
    bool Visible;
    bool SimulatePhysics;
    bool UseAsymmetricGravity;
    float Rotation;

    bool isInPlay;
   
};