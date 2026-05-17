/** @file Tickable.hpp */
#pragma once

/**
 * @brief Abstract class that route ticking functionality
 * @note This class \em must be inherited from for object classes that should tick.
 * This class has no inherent functionality.
 */
class Tickable 
{
public:

    /** @brief Checks if object is ticking @returns true if object is ticking */
    bool isTicking() const;
    /** @brief Sets tick state for object @param isEnabled tick state */
    void SetTicking(bool isEnabled);

protected:
    Tickable() = default; // protected constructor lets ONLY derived classes call it
    virtual ~Tickable() = 0; // protected destructor stops compiler from allocating new, pure virtual makes abstract

    /**
     * @brief Update tick event
     * @details This function is called every tick on the update step. Put all gameplay
     * functionality that should run every update here (custom movement logic, etc.)
     * @param dt Deltatime; time elapsed since last frame in ms
     * @note Always call base method when overriding: TODO
     * @code
     * void Class::Tick() {
     *     BaseClass::Tick();
     *     // ...
     * }
     * @endcode
     */
    virtual void Tick(float dt);

private:
    bool bTicking;

};