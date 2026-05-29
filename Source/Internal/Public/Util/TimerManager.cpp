
#include "Debug/Debug.hpp"

#include "TimerManager.hpp"

TimerManager::TimerManager() {
    LOG_DEFAULT(LogType::VITAL, "TimerManager constructed");

    SetTicking(true);
}

void TimerManager::Tick([[maybe_unused]] float dt) {

    if (!PendingTimers.empty()) {
        ActiveTimers.insert(ActiveTimers.end(), std::make_move_iterator(PendingTimers.begin()), std::make_move_iterator(PendingTimers.end()));
        PendingTimers.clear();
    }

    std::vector<Timer> haltedTimers;

    for (auto it = ActiveTimers.begin(); it != ActiveTimers.end();) {
        Timer& timer = *it;

        if (timer.IsFinished()) {
            it = ActiveTimers.erase(it);
            continue; 
        }

        if (timer.IsUpdating()) {
            timer.UpdateTick(dt);
        }

        if (timer.IsFinished()) {
            it = ActiveTimers.erase(it);
        } else {
            ++it;
        }
    }
}

void TimerManager::HaltTimer(const std::string &name) {
    for (Timer& timer : ActiveTimers) {
        if (timer.GetName() == name) {
            timer.Halt();
        }
    }
    for (Timer& timer : PendingTimers) {
        if (timer.GetName() == name) {
            timer.Halt();
        }
    }
}

void TimerManager::PauseTimer(const std::string &name) {
    for (Timer& timer : ActiveTimers) {
        if (timer.GetName() == name) {
            timer.SetUpdating(false);
        }
    }
}

void TimerManager::ResumeTimer(const std::string &name) {
    for (Timer& timer : ActiveTimers) {
        if (timer.GetName() == name) {
            timer.SetUpdating(true);
        }
    }
}

bool TimerManager::IsTimerActive(const std::string &name) const {
    for (const Timer& timer : ActiveTimers) {
        if (timer.GetName() == name) {
            return true;
        }
    }

    return false;
}

Timer& TimerManager::GetTimer(const std::string &name) {
    for (Timer& timer : ActiveTimers) {
        if (timer.GetName() == name) {
            return timer;
        }
    }

    LOG_DEFAULT(LogType::ERROR, "Timer with name '{}' not found", name);
    throw std::runtime_error("Timer not found");
}

TimerManager::~TimerManager() {
    LOG_DEFAULT(LogType::VITAL, "TimerManager destroying");
}