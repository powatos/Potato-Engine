/** @file Actor.hpp */
#pragma once

#include "Core/Datastore/Archivable.hpp"
#include "Core/Event/Tickable.hpp"
#include "Util/Vector2.hpp"

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
     * @details Put all pre-gameplay functionality here TODO: examples
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

    bool Visible;

    Vector2 Position;
    Vector2 Size;
    float Rotation;

    bool isInPlay;
   
};