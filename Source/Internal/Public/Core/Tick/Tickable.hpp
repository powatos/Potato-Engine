/** @file Tickable.hpp */
#pragma once

class TickController;

/**
 * @brief Abstract class that route ticking functionality
 * @note This class \em must be inherited from for object classes that should tick.
 * This class has no inherent functionality.
 */
class Tickable 
{
    friend class TickController;

public:
    Tickable(Tickable&&) noexcept = default;
    Tickable& operator =(Tickable&&) noexcept = default;

protected:
    Tickable(); // protected constructor lets ONLY derived classes call it
    virtual ~Tickable() = 0; // protected destructor stops compiler from allocating new, pure virtual makes abstract

    /**
     * @brief Pre-input update event
     * @details This function is called every tick before the input handling step. Put all gameplay
     * functionality that should run before input handling here
     * @param dt Deltatime; time elapsed since last frame in ms
     * @note Always call base method when overriding: 
     * @code
     * void Class::TickPreInput() {
     *     BaseClass::TickPreInput();
     *     // ...
     * }
     * @endcode
     */
    virtual void TickPreInput(float dt) {}
    /**
     * @brief Update tick event
     * @details This function is called every tick on the update step. Put all gameplay
     * functionality that should run every update here (custom movement logic, etc.)
     * @param dt Deltatime; time elapsed since last frame in ms
     * @note Always call base method when overriding: 
     * @code
     * void Class::Tick() {
     *     BaseClass::Tick();
     *     // ...
     * }
     * @endcode
     */
    virtual void Tick(float dt) {};
    /**
     * @brief Post-physics update event
     * @details This function is called every tick on the post-physics step. Put all
     * functionality that should run after physics updates here.
     * @param dt Deltatime; time elapsed since last frame in ms
     * @note Always call base method when overriding: 
     * @code
     * void Class::TickPostPhysics() {
     *     BaseClass::TickPostPhysics();
     *     // ...
     * }
     * @endcode
     */
    virtual void TickPostPhysics(float dt) {}
    /**
     * @brief Post-render update event
     * @details This function is called every tick on the post-render step. Put all
     * functionality that should run after rendering here.
     * @param dt Deltatime; time elapsed since last frame in ms
     * @note Always call base method when overriding: 
     * @code
     * void Class::TickPostRender() {
     *     BaseClass::TickPostRender();
     *     // ...
     * }
     * @endcode
     */
    virtual void TickPostRender(float dt) {}

    bool bTickingPreInput;
    bool bTickingUpdate;
    bool bTickingPostPhysics;
    bool bTickingPostRender;

};
