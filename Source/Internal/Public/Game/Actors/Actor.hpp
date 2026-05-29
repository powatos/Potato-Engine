/** @file Actor.hpp */
#pragma once

#include "Core/Data/Archivable.hpp"
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
    
    Vector2 GetPosition() const; /**< @brief Gets position @returns Position */
    void SetPosition(const Vector2& position); /**< @brief Sets position @param position Position to set */
    void AddLocalOffset(const Vector2& offset); /**< @brief Adds to location vector @param offset Offset to add */

    Vector2 GetSize() const; /**< @brief Gets size @returns Size */
    void SetSize(const Vector2& size); /**< @brief Sets size @param size Size to set */

    float GetRotation() const; /**< @brief Gets rotation @returns rotation */
    void SetRotation(float rotation); /**< @brief Sets rotation @param rotation Rotation to set (degrees) */
    void AddLocalRotation(float rotation); /**< @brief Adds to rotation value @param rotation Rotation to add */

    bool isVisible() const; /**< @brief Checks if actor visible @returns true if visible */
    void SetVisibility(bool visibility); /**< @brief Sets visibility of actor @param visibility Visibility to set */

    Vector2 GetVelocity() const; /**< @brief Gets velocity @returns Velocity */
    void SetVelocity(const Vector2& velocity); /**< @brief Sets velocity @param velocity Velocity to set */
    void AddImpulse(const Vector2& force); /**< @brief Adds impulse to velocity @param force Impulse to add */
    
    float GetMass() const; /**< @brief Gets mass @returns Mass */
    void SetMass(float mass); /**< @brief Sets mass @param mass Mass to set */

    bool isSimulatingPhysics() const; /**< @brief Checks if simulating physics @returns true if simulating physics */
    void SetSimulatingPhysics(bool enabled); /**< @brief Sets physics simulation @param enabled Whether to simulate physics */

    Vector2 GetForces() const; /**< @brief Gets forces applied to actor in current tick @returns Forces */
    void AddForce(const Vector2& force); /**< @brief Adds force to actor @param force Force to add */
    void ClearForces(); /**< @brief Clears all forces applied to actor */

    bool IsUsingAsymmetricGravity() const; /**< @brief Checks if actor is using asymmetric gravity @returns true if using asymmetric gravity */
    void SetUseAsymmetricGravity(bool useAsymmetricGravity); /**< @brief Sets whether actor should use asymmetric gravity @param useAsymmetricGravity Whether to use asymmetric gravity */

    ActorMovability GetMovability() const; /**< @brief Gets movability @returns Movability */
    void SetMovability(ActorMovability movability); /**< @brief Sets movability @param movability Movability to set */

    float GetBounce() const; /**< @brief Gets bounce @returns Bounce */
    void SetBounce(float bounce); /**< @brief Sets bounce @param bounce Bounce to set */

    /**
     * @brief Internal function used to queue BeginPlay() on actor
     */
    void DispatchBeginPlay();

    /**
     * @brief Single-char texture for actor
     * @details The actor is displayed as a grid (based on its @ref GetSize() "size") of this character
     */
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
    
    virtual void Tick([[maybe_unused]] float dt) override;

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