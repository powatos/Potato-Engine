/** @file TimerManager.hpp */
#pragma once

#include <vector>

#include "Timer.hpp"

#include "Core/Event/Tickable.hpp"

/**
 * @brief Class that interfaces and handles all timers
 */
class TimerManager : public Tickable
{
    TimerManager();
    ~TimerManager(); 
    TimerManager(const TimerManager&) = delete;
    TimerManager& operator = (const TimerManager&) = delete;
    TimerManager(TimerManager&&) = delete;
    TimerManager& operator = (TimerManager&&) = delete;
public:
    /**
     * @brief Gets singleton instance
     * @returns instance
     */
    static TimerManager* get();

    /**
     * @brief Creates a new timer
     * @warning The timer returned will go out of scope at the end of the tick it was 
     * added
     * @param duration Duration of the timer
     * @returns An unsafe reference to created timer
     */
    template<typename T>
    Timer& AddTimer(std::string name, double duration, T* obj, void(T::*callback)());

    /**
     * @brief Halts an ongoing timer
     * @param name Name of timer to halt
     */
    void HaltTimer(const std::string& name);

    /**
     * @brief Pauses an ongoing timer
     * @param name Name of timer to pause
     */
    void PauseTimer(const std::string& name);

    /**
     * @brief Resumes a paused timer
     * @param name Name of timer to resume
     */
    void ResumeTimer(const std::string& name);  

    /**
     * @brief Checks if a timer is active (being managed)
     * @note Timers may be halted but still active
     * @param name Name of timer to check
     * @returns true if timer exists
     */
    bool IsTimerActive(const std::string& name) const;

    /**
     * @brief Gets a timer by name
     * @param name Name of timer to get
     * @warning Getting a timer reference on the same tick it was created is undefined
     * behaviour
     * @warning Ensure timer exists before calling this method. @sa IsTimerActive
     */
    Timer& GetTimer(const std::string& name);

protected:
    virtual void Tick([[maybe_unused]] float dt) override;

private:
    std::vector<Timer> ActiveTimers;
    std::vector<Timer> PendingTimers;
};

template<typename T>
inline Timer& TimerManager::AddTimer(std::string name, double duration, T* obj, void(T::*callback)()) {
    return PendingTimers.emplace_back(
        name,
        duration,
        obj,
        callback

    );
}
