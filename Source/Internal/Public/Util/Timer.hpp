/** @file Timer.hpp */
#pragma once

#include "Core/Event/EventDelegate.hpp"

/**
 * @brief Simple timer for scheduling and tracking
 * @warning Do not mutate timers manually. Use the TimerManager interface exposed by the engine instead. @sa TimerManager
 */
struct Timer
{
private:
    std::string name;
    std::string eventName;
    // NativeEventBinding<> binding;
    EventDelegate<> delegate;
    double duration;
    double elapsed;
    bool hasFinished;
    bool isUpdating;


public:
    /**
     * @brief Constructs timer object
     * @param timerName Name of timer
     * @warning Do not manage timers manually. @sa TimerManager
     * @param duration Duration of timer in seconds
     */
    template<typename T>
    Timer(std::string timerName, double duration, T* obj, void(T::*callback)()) :
        name(std::move(timerName)),
        eventName("__TIMER_" + name),
        // binding(eventName, obj, callback),
        delegate(obj, callback),
        duration(duration),
        elapsed(0.0),
        hasFinished(false),
        isUpdating(true)
    {}

    /** @brief Gets name of timer @returns name */
    const std::string& GetName() const { return name; }
    /** @brief Gets duration of timer @returns duration in seconds */
    double GetDuration() const { return duration; }
    /** @brief Gets elapsed time of timer @returns elapsed time in seconds */
    double GetElapsed() const { return elapsed; }
    /** @brief Checks if timer has finished @returns true if finished */
    bool IsFinished() const { return hasFinished; }
    /** @brief Checks if timer is currently updating @returns true if updating */
    bool IsUpdating() const { return isUpdating; }

    /**
     * @brief Updates timer for current tick
     * @warning This method is for internal managing use only. Do not manage timers manually. @sa TimerManager
     * @param elsapsed Time since last update
     */
    inline void UpdateTick(const float elapsed) {
        if (hasFinished) { return; }

        this->elapsed += elapsed;
        if (this->elapsed >= duration) {
            Complete();
        }
    }

    /**
     * @brief Halts this timer permanently
     * @warning This method is for internal managing use only. Do not manage timers manually. @sa TimerManager
     */
    inline void Halt() { hasFinished = true; }

    /**
     * @brief Changes the updating state of the timer
     * @warning This method is for internal managing use only. Do not manage timers manually. @sa TimerManager
     */
    inline void SetUpdating(bool updating) { isUpdating = updating; }
protected:

    inline void Complete() {
        if (hasFinished) { return; }
        hasFinished = true;

        delegate.Fire();
    }
};
